/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltammie <ltammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 18:55:55 by ltammie           #+#    #+#             */
/*   Updated: 2020/02/01 09:50:26 by sauron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

t_mlx	*start()
{
	t_mlx *data;

	if (!(data = (t_mlx *)malloc(sizeof(t_mlx))))
		suicide(ERR_MALLOC);
	if (!(data->mlx = mlx_init()))
		suicide(ERR_START_INIT);
	if (!(data->window = mlx_new_window(data->mlx, W, H, "Cake is a lie")))
		suicide(ERR_START_WIN);
	data->cam.zoom = 1;
	data->cam.x_shift = 0;
	data->cam.y_shift = 0;
	data->cam.x_angle = 0;
	data->cam.y_angle = 0;
	data->cam.z_angle = 0;
	data->cam.z_level = 1;
	data->cam.projection = 'I';
	return (data);
}
