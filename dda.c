/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltammie <ltammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 15:29:39 by ltammie           #+#    #+#             */
/*   Updated: 2020/02/01 09:24:52 by sauron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

static void rotate_x(double *y, double *z, t_mlx *data)
{
	double prev_y;
	double x_angle;

	prev_y = *y;
	x_angle = dtr(data->cam.x_angle);
	*y = prev_y * cos(x_angle) + *z * sin(x_angle);
	*z = -prev_y * sin(x_angle) + *z * cos(x_angle);
}

static void rotate_y(double *x, double *z, t_mlx *data)
{
	double prev_x;
	double y_angle;

	prev_x = *x;
	y_angle = dtr(data->cam.y_angle);
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
	z_angle = dtr(data->cam.z_angle);
	*x = prev_x * cos(z_angle) - prev_y * sin(z_angle);
	*y = prev_x * sin(z_angle) + prev_y * cos(z_angle);
}

void	dda(t_mlx *data, t_point p1, t_point p2)
{
	double dx;
	double dy;
	int max;
	int color;

	color = (p1.z || p2.z) ? 0xff0000 : 0xffffff;
	p1.x = p1.x * data->cam.zoom;
	p1.y = p1.y * data->cam.zoom;
	p1.z = p1.z * data->cam.z_level;
	p2.x = p2.x * data->cam.zoom;
	p2.y = p2.y * data->cam.zoom;
	p2.z = p2.z * data->cam.z_level;;
	rotate_x(&p1.y, &p1.z, data);
	rotate_x(&p2.y, &p2.z, data);
	rotate_y(&p1.x, &p1.z, data);
	rotate_y(&p2.x, &p2.z, data);
	rotate_z(&p1.x, &p1.y, data);
	rotate_z(&p2.x, &p2.y, data);
	if (data->cam.projection == 'C')
	{
		cavalier(&p1.x, &p1.y, p1.z);
		cavalier(&p2.x, &p2.y, p2.z);
	}
	else if (data->cam.projection == 'I')
	{
		iso(&p1.x, &p1.y, p1.z);
		iso(&p2.x, &p2.y, p2.z);
	}
	else if (data->cam.projection == 'V')
	{
		cabinet(&p1.x, &p1.y, p1.z);
		cabinet(&p2.x, &p2.y, p2.z);
	}
	else if (data->cam.projection == 'L')
	{
		perspective(&p1.x, &p1.y, &p1.z);
		perspective(&p2.x, &p2.y, &p2.z);
	}
	p1.x += imW / 2;
	p1.y += imH / 2;
	p2.x += imW / 2;
	p2.y += imH / 2;
	p1.x += data->cam.x_shift;
	p1.y += data->cam.y_shift;
	p2.x += data->cam.x_shift;
	p2.y += data->cam.y_shift;
	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	max = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
	dx = dx / max;
	dy = dy / max;
	while ((int)(p1.x - p2.x) || (int)(p1.y - p2.y))
	{
		if ((int)p1.x >= 0 && (int)p1.x < imW && (int)p1.y >= 0 && (int)p1.y <imH)
			data->image.img_data[(int)(p1.y) * imW + (int)p1.x] = color;
		p1.x += dx;
		p1.y += dy;
	}
}
