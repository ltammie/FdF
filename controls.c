/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sauron <sauron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 00:42:58 by sauron            #+#    #+#             */
/*   Updated: 2020/01/18 16:09:32 by ltammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

int		move(int key, t_mlx *data)
{
	if (key == 123)
		data->cam.x_shift -= 10;
	if (key == 124)
		data->cam.x_shift += 10;
	if (key == 125)
		data->cam.y_shift += 10;
	if (key == 126)
		data->cam.y_shift -= 10;
	mlx_clear_window(data->mlx, data->window);
	draw_image(data);
	return (0);
}

int		zoom(int key, t_mlx *data)
{
	if (key == 27)
	{
		if (data->cam.zoom != 1)
			data->cam.zoom--;
	}
	if (key == 24)
		data->cam.zoom++;
	mlx_clear_window(data->mlx, data->window);
	draw_image(data);
	return (0);
}

int		rotate(int key, t_mlx *data)
{
	if (key == 0)
		data->cam.x_angle -= 10.0;
	if (key == 2)
		data->cam.x_angle += 10.0;
	if (key == 13)
		data->cam.y_angle += 10.0;
	if (key == 1)
		data->cam.y_angle -= 10.0;
	if (key == 12)
		data->cam.z_angle -= 10.0;
	if (key == 14)
		data->cam.z_angle += 10.0;
	if (fabs(data->cam.x_angle) >= 360.0)
		data->cam.x_angle = fabs(data->cam.x_angle) - (360.0);
	if (fabs(data->cam.y_angle) >= 360.0)
		data->cam.y_angle = fabs(data->cam.y_angle) - (360.0);
	if (fabs(data->cam.z_angle) >= 360.0)
		data->cam.z_angle = fabs(data->cam.z_angle) - (360.0);=
	mlx_clear_window(data->mlx, data->window);
	draw_image(data);
	return (0);
}

int 	flattening(int key, t_mlx *data)
{
	if (key == 15)
		data->cam.z_level += 1;
	if (key == 3)
		data->cam.z_level -= 1;
	mlx_clear_window(data->mlx, data->window);
	draw_image(data);
	return (0);
}

void 	close_fdf(int key, t_mlx *data)
{
	if (key == 53)
	{
		mlx_destroy_image(data->mlx, data->image.img_ptr);
		mlx_destroy_window(data->mlx,data->window);
		exit(0);
	}
}
