/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltammie <ltammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 16:33:12 by ltammie           #+#    #+#             */
/*   Updated: 2020/02/24 18:19:53 by ltammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

int		key_press(int key, t_mlx *data)
{
	if (key == AR_LEFT || key == AR_RIGHT || key == AR_DOWN || key == AR_UP)
		move(key, data);
	if (key == MIN || key == PlUS)
		zoom(key, data);
	if (key == A || key == S || key == D || key == Q || key == W || key == E)
		rotate(key, data);
	if (key == R || key == F)
		flattening(key, data);
	if (key == P)
	{
		camera_init(data);
		if (data->cam.proj == 'I')
			data->cam.proj = 'C';
		else if (data->cam.proj == 'C')
			data->cam.proj = 'V';
		else if (data->cam.proj == 'V')
			data->cam.proj = 'L';
		else
			data->cam.proj = 'I';
		mlx_clear_window(data->mlx, data->win);
		draw_image(data);
	}
	if (key == ESC)
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
	mlx_hook(data->win, 2, (1L << 0), key_press, data);
	mlx_loop(data->mlx);
	return (0);
}
