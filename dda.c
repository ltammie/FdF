/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltammie <ltammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 15:29:39 by ltammie           #+#    #+#             */
/*   Updated: 2020/01/28 15:50:42 by ltammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

static void	iso(double *x, double *y, int z)
{
	double prev_x;
	double prev_y;

	prev_x = *x;
	prev_y = *y;

	*x = (prev_x - prev_y) * cos(degToRad(iso_angle));
	*y = (prev_x + prev_y) * sin(degToRad(iso_angle)) - z;
}

static void rotate_x(double *y, double *z, t_mlx *data)
{
	double prev_y;
	double x_angle;

	prev_y = *y;
	x_angle = degToRad(data->cam.x_angle);
	*y = prev_y * cos(x_angle) + *z * sin(x_angle);
	*z = -prev_y * sin(x_angle) + *z * cos(x_angle);
}

static void rotate_y(double *x, double *z, t_mlx *data)
{
	double prev_x;
	double y_angle;

	prev_x = *x;
	y_angle = degToRad(data->cam.y_angle);
	*x = prev_x * cos(y_angle) + *z * sin(y_angle);
	*z = -prev_x * sin(y_angle) + *z * cos(y_angle);
}

static void rotate_z(double *x, double *y, t_mlx *data)
{
	double prev_x;
	double prev_y;
	double z_angle;

	prev_x = *x;
	prev_y = *y;
	z_angle = degToRad(data->cam.z_angle);
	*x = prev_x * cos(z_angle) - prev_y * sin(z_angle);
	*y = prev_x * sin(z_angle) + prev_y * cos(z_angle);
}

void	dda(t_mlx *data, t_point p1, t_point p2)
{
	double x;
	double y;
	double z;
	double x1;
	double y1;
	double z1;
	double dx;
	double dy;
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

	x += imW / 2;
	y += imH / 2;
	x1 += imW / 2;
	y1 += imH / 2;

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
