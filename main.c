/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltammie <ltammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 16:33:12 by ltammie           #+#    #+#             */
/*   Updated: 2020/02/01 09:03:22 by sauron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"
#include <stdio.h>

int 	key_press(int key, t_mlx *data)
{
	if (key == ARROW_LEFT || key == ARROW_RIGHT || key == ARROW_DOWN || key == ARROW_UP)
		move(key, data);
	else if (key == MIN || key == PlUS)
		zoom(key, data);
	else if (key == A || key == S || key == D || key == Q || key == W || key == E)
		rotate(key, data);
	else if (key == R || key == F)
		flattening(key, data);
	else if (key == P)
	{
		camera_init(data);
		if (data->cam.projection == 'I')
			data->cam.projection = 'C';
		else if (data->cam.projection == 'C')
			data->cam.projection = 'V';
		else if (data->cam.projection == 'V')
			data->cam.projection = 'L';
		else
			data->cam.projection = 'I';
		mlx_clear_window(data->mlx, data->window);
		draw_image(data);
	}
	else if (key == ESC)
		close_fdf(data);
	return (0);
}

int		main(int argc, char **argv)
{
	t_mlx	*data;

	if (argc != 2)
		suicide(ERR_ARGV);
	data = start();
	read_map_data(argv[1], data);
	draw_image(data);
	mlx_hook(data->window, 2, (1L<<0), key_press, data);
	mlx_loop(data->mlx);
	return (0);
}
