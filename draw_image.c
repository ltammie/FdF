/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltammie <ltammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 15:01:33 by ltammie           #+#    #+#             */
/*   Updated: 2020/02/24 18:04:52 by ltammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

static void draw_background(t_mlx *data)
{
	int i;
	int j;

	i = -1;
	while (++i < imH)
	{
		j= -1;
		while (++j < imW)
		{
			data->img.img_data[i * imW + j] = 0;
		}
	}
}

static	void image_init(t_mlx *data)
{
	data->img.img_ptr = mlx_new_image(data->mlx, imW, imH);
	data->img.img_data = (int *)mlx_get_data_addr(data->img.img_ptr,
			&data->img.bpp, &data->img.size_l, &data->img.endian);
	draw_background(data);
}

static	int	get_color(t_point p1, t_point p2)
{
	int color;

	color = (p1.z || p2.z) ? 0xff0000 : 0xffffff;
	return (color);
}

void	draw_image(t_mlx *data)
{
	int	i;
	int	j;
	int	color;

	image_init(data);
	i = -1;
	while (++i < data->map.mH)
	{
		j = -1;
		while (++j < data->map.mW)
		{
			if (j < data->map.mW - 1)
			{
				color = get_color(data->map.m[i * data->map.mW + j],
								  data->map.m[i * data->map.mW + (j + 1)]);
				dda(data, data->map.m[i * data->map.mW + j],
					data->map.m[i * data->map.mW + (j + 1)], color);
			}
			if (i < data->map.mH - 1)
			{
				color = get_color(data->map.m[i * data->map.mW + j],
								  data->map.m[(i + 1) * data->map.mW + j]);
				dda(data, data->map.m[i * data->map.mW + j],
					data->map.m[(i + 1) * data->map.mW + j], color);
			}
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
	mlx_string_put(data->mlx, data->win, 200, 200, 0xff0000, &data->cam.projection);
}
