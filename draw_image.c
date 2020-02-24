/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltammie <ltammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 15:01:33 by ltammie           #+#    #+#             */
/*   Updated: 2020/02/24 18:20:33 by ltammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

static	void	draw_background(t_mlx *data)
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

static	void	image_init(t_mlx *data)
{
	data->img.img_ptr = mlx_new_image(data->mlx, imW, imH);
	data->img.img_data = (int *)mlx_get_data_addr(data->img.img_ptr,
			&data->img.bpp, &data->img.size_l, &data->img.endian);
	draw_background(data);
}

static	int		get_color(t_point p1, t_point p2)
{
	int color;

	color = (p1.z || p2.z) ? 0xff0000 : 0xffffff;
	return (color);
}

void			draw_image(t_mlx *d)
{
	int	i;
	int	j;
	int	color;

	image_init(d);
	i = -1;
	while (++i < d->m.mH)
	{
		j = -1;
		while (++j < d->m.mW)
		{
			if (j < d->m.mW - 1)
			{
				color = get_color(d->m.m[i * d->m.mW + j],
						d->m.m[i * d->m.mW + (j + 1)]);
				dda(d, d->m.m[i * d->m.mW + j],
						d->m.m[i * d->m.mW + (j + 1)], color);
			}
			if (i < d->m.mH - 1)
			{
				color = get_color(d->m.m[i * d->m.mW + j],
						d->m.m[(i + 1) * d->m.mW + j]);
				dda(d, d->m.m[i * d->m.mW + j],
						d->m.m[(i + 1) * d->m.mW + j], color);
			}
		}
	}
	mlx_put_image_to_window(d->mlx, d->win, d->img.img_ptr, 0, 0);
	mlx_string_put(d->mlx, d->win, 200, 200, 0xff0000, &d->cam.proj);
}
