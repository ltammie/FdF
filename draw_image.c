/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltammie <ltammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 15:01:33 by ltammie           #+#    #+#             */
/*   Updated: 2020/02/24 18:36:58 by ltammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

void			draw_background(t_mlx *data)
{
	int i;
	int j;

	i = -1;
	while (++i < imH)
	{
		j = -1;
		while (++j < imW)
		{
			data->img.img_data[i * imW + j] = 0;
		}
	}
}

static	int		get_color(t_point p1, t_point p2)
{
	int color;

	color = (p1.z > p2.z) ? p1.color : p2.color;
	return (color);
}

static	void	draw_horizontal_line(t_mlx *d, int i, int j)
{
	int	color;

	color = get_color(d->m.m[i * d->m.mW + j],
			d->m.m[i * d->m.mW + (j + 1)]);
	dda(d, d->m.m[i * d->m.mW + j],
			d->m.m[i * d->m.mW + (j + 1)], color);
}

static	void	draw_vertical_line(t_mlx *d, int i, int j)
{
	int	color;

	color = get_color(d->m.m[i * d->m.mW + j],
			d->m.m[(i + 1) * d->m.mW + j]);
	dda(d, d->m.m[i * d->m.mW + j],
			d->m.m[(i + 1) * d->m.mW + j], color);
}

void			draw_image(t_mlx *d)
{
	int	i;
	int	j;

	image_init(d);
	i = -1;
	while (++i < d->m.mH)
	{
		j = -1;
		while (++j < d->m.mW)
		{
			if (j < d->m.mW - 1)
				draw_horizontal_line(d, i, j);
			if (i < d->m.mH - 1)
				draw_vertical_line(d, i, j);
		}
	}
	mlx_put_image_to_window(d->mlx, d->win, d->img.img_ptr, 200, 200);
	draw_menu(d);
}
