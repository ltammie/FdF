/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltammie <ltammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 16:33:12 by ltammie           #+#    #+#             */
/*   Updated: 2020/01/28 16:17:00 by ltammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"
#include <stdio.h>

int 	key_press(int key, t_mlx *data)
{

	if (key == 123 || key == 124 || key == 125 || key == 126)
		move(key, data);
	else if (key == 27 || key == 24)
		zoom(key, data);
	else if (key == 0 || key == 1 || key == 2 || key == 12 || key == 13 || key == 14)
		rotate(key, data);
	else if (key == 15 || key == 3)
		flattening(key, data);
	else if (key == 53)
		close_fdf(data);
	return (0);
}

int 	key_release(int key, t_mlx *data)
{
	if (key && data)
		return (0);
	return (0);
}

int		main(int argc, char **argv)
{
	t_mlx	*data;

	if (argc != 2)
		suicide(ERR_ARGV);
	data = start();
	read_map_data(argv[1], data);
	printf("x0 = %d\ny0 = %d\n", data->map.x0, data->map.y0);
	draw_image(data);
	mlx_hook(data->window, 2, (1L<<0), key_press, data);
	mlx_hook(data->window, 3, (1L<<1), key_release, data);
	mlx_loop(data->mlx);
	return (0);
}
