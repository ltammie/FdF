/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltammie <ltammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 18:55:55 by ltammie           #+#    #+#             */
/*   Updated: 2020/02/24 17:35:33 by ltammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

void	camera_update(t_mlx *data)
{
	data->cam.x_sin = sin(dtr(data->cam.x_angle));
	data->cam.x_cos = cos(dtr(data->cam.x_angle));
	data->cam.y_sin = sin(dtr(data->cam.y_angle));
	data->cam.y_cos = cos(dtr(data->cam.y_angle));
	data->cam.z_sin = sin(dtr(data->cam.z_angle));
	data->cam.z_cos = cos(dtr(data->cam.z_angle));
}


void	camera_init(t_mlx *data)
{
	data->cam.zoom = 10;
	data->cam.x_shift = 0;
	data->cam.y_shift = 0;
	data->cam.z_level = 1;
	data->cam.x_angle = 0;
	data->cam.y_angle = 0;
	data->cam.z_angle = 0;
	camera_update(data);
}

t_mlx	*start(void)
{
	t_mlx *data;

	if (!(data = (t_mlx *)malloc(sizeof(t_mlx))))
		suicide(ERR_MALLOC);
	if (!(data->mlx = mlx_init()))
		suicide(ERR_START_INIT);
	if (!(data->window = mlx_new_window(data->mlx, WIDTH, HEIGHT, "fdf")))
		suicide(ERR_START_WIN);
	camera_init(data);
	data->cam.projection = 'I';
	return (data);
}
