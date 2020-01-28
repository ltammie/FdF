	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltammie <ltammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 15:01:33 by ltammie           #+#    #+#             */
/*   Updated: 2020/01/15 02:15:22 by sauron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

/*
 ** i for rows, j for columns
 */

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
			data->image.img_data[i * imW + j] = 0;
		}
	}
}

void	draw_image(t_mlx *data)
{
	int i;
	int j;

	data->image.img_ptr = mlx_new_image(data->mlx, imW, imH);
	data->image.img_data = (int* )mlx_get_data_addr(data->image.img_ptr,
			&data->image.bpp, &data->image.size_l, &data->image.endian);
	draw_background(data);
	i = -1;
	while (++i < data->map.mH)
	{
		j= -1;
		while (++j < data->map.mW)
		{
			if (j < data->map.mW -1)
				dda(data, data->map.grid[i * data->map.mW + j],data->map.grid[i * data->map.mW + (j + 1)]);
			if (i < data->map.mH -1)
				dda(data, data->map.grid[i * data->map.mW + j],data->map.grid[(i + 1) * data->map.mW + j]);
		}
	}
	mlx_put_image_to_window(data->mlx, data->window, data->image.img_ptr, 0, 0);
}
