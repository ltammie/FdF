/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltammie <ltammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 15:29:39 by ltammie           #+#    #+#             */
/*   Updated: 2020/02/24 18:10:44 by ltammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

void	dda(t_mlx *data, t_point p1, t_point p2, int color)
{
	double	dx;
	double	dy;
	double	max;

	point_convert(data, &p1, &p2);

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	max = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
	dx = dx / max;
	dy = dy / max;
	while ((int)(p1.x - p2.x) || (int)(p1.y - p2.y))
	{
		if ((int)p1.x >= 0 && (int)p1.x < imW && (int)p1.y >= 0 && (int)p1.y <imH)
			data->img.img_data[(int)(p1.y) * imW + (int)p1.x] = color;
		p1.x += dx;
		p1.y += dy;
	}
}
