/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltammie <ltammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 15:29:39 by ltammie           #+#    #+#             */
/*   Updated: 2020/01/28 18:47:41 by ltammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

//static void	iso(double *x, double *y, int z)
//{
//	double prev_x;
//	double prev_y;
//
//	prev_x = *x;
//	prev_y = *y;
//
//	*x = (prev_x - prev_y) * cos(degToRad(iso_angle));
//	*y = (prev_x + prev_y) * sin(degToRad(iso_angle)) - z;
//}

static	void	cavalier(double *x, double *y, int z)
{
	double prev_x;
	double prev_y;

	prev_x = *x;
	prev_y = *y;

	*x = prev_x - z * cos(degToRad(oblique_angle));
	*y = prev_y - z * sin(degToRad(oblique_angle));
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
	t_point a;
	t_point b;
	double dx;
	double dy;
	int max;
	int color;

	a.x = p1.x * data->cam.zoom;
	a.y = p1.y * data->cam.zoom;
	a.z = p1.z * data->cam.z_level;
	b.x = p2.x * data->cam.zoom;
	b.y = p2.y * data->cam.zoom;
	b.z = p2.z * data->cam.z_level;;
	rotate_x(&a.y, &a.z, data);
	rotate_x(&b.y, &b.z, data);
	rotate_y(&a.x, &a.z, data);
	rotate_y(&b.x, &b.z, data);
	rotate_z(&a.x, &a.y, data);
	rotate_z(&b.x, &b.y, data);
	color = (p1.z || p2.z) ? 0xff0000 : 0xffffff;
	cavalier(&a.x, &a.y, a.z);
	cavalier(&b.x, &b.y, b.z);
//	iso(&a.x, &a.y, a.z);
//	iso(&b.x, &b.y, b.z);
	a.x += imW / 2;
	a.y += imH / 2;
	b.x += imW / 2;
	b.y += imH / 2;
	a.x += data->cam.x_shift;
	a.y += data->cam.y_shift;
	b.x += data->cam.x_shift;
	b.y += data->cam.y_shift;
	dx = b.x - a.x;
	dy = b.y - a.y;
	max = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
	dx = dx / max;
	dy = dy / max;
	while ((int)(a.x - b.x) || (int)(a.y - b.y))
	{
		if ((int)a.x >= 0 && (int)a.x < imW && (int)a.y >= 0 && (int)a.y <imH)
			data->image.img_data[(int)(a.y) * imW + (int)a.x] = color;
		a.x += dx;
		a.y += dy;
	}
}
