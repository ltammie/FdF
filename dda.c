/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltammie <ltammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 15:29:39 by ltammie           #+#    #+#             */
/*   Updated: 2020/01/17 06:53:24 by sauron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

static void	iso(float *x, float *y, int z)
{
	float prev_x;
	float prev_y;

	prev_x = *x;
	prev_y = *y;

	*x = (prev_x - prev_y) * cos(iso_angle);
	*y = (prev_x + prev_y) * sin(iso_angle) - z;
}

static void rotate_x(float *y, float *z, t_mlx *data)
{
	float prev_y;

	prev_y = *y;
	*y = prev_y * cos(data->cam.x_angle) + *z * sin(data->cam.x_angle);
	*z = -prev_y * sin(data->cam.x_angle) + *z * cos(data->cam.x_angle);
}

static void rotate_y(float *x, float *z, t_mlx *data)
{
	float prev_x;

	prev_x = *x;
	*x = prev_x * cos(data->cam.y_angle) + *z * sin(data->cam.y_angle);
	*z = -prev_x * sin(data->cam.y_angle) + *z * cos(data->cam.y_angle);
}

static void rotate_z(float *x, float *y, t_mlx *data)
{
	float prev_x;
	float prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = prev_x * cos(data->cam.z_angle) - prev_y * sin(data->cam.z_angle);
	*y = prev_x * sin(data->cam.z_angle) + prev_y * cos(data->cam.z_angle);
}

void	dda(t_mlx *data, t_point p1, t_point p2)
{
	float x;
	float y;
	float z;
	float x1;
	float y1;
	float z1;
	float dx;
	float dy;
	int max;
	int color;

	x = p1.x * data->cam.zoom;
	y = p1.y * data->cam.zoom;
	x1 = p2.x * data->cam.zoom;
	y1 = p2.y * data->cam.zoom;
	z = p1.z * data->cam.z_level;
	z1 = p2.z * data->cam.z_level;;

	rotate_x(&y, &z, data);
	rotate_x(&y1, &z1, data);
	rotate_y(&x, &z, data);
	rotate_y(&x1, &z1, data);
	rotate_z(&x, &y, data);
	rotate_z(&x1, &y1, data);
	color = (p1.z || p2.z) ? 0xff0000 : 0xffffff;
	iso(&x, &y, z);
	iso(&x1, &y1, z1);

	x += data->cam.x_shift;
	y += data->cam.y_shift;
	x1 += data->cam.x_shift;
	y1 += data->cam.y_shift;

	dx = x1 - x;
	dy = y1 - y;
	max = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
	dx = dx / max;
	dy = dy / max;
	while ((int)(x - x1) || (int)(y - y1))
	{
		if ((int)x >= 0 && (int)x < imW && (int)y >= 0 && (int)y <imH)
			data->image.img_data[(int)(y) * imW + (int)x] = color;
		x += dx;
		y += dy;
	}
}
