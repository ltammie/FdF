/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltammie <ltammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 17:15:31 by ltammie           #+#    #+#             */
/*   Updated: 2020/02/24 17:16:44 by ltammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

void	iso(double *x, double *y, double z)
{
	double prev_x;
	double prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = (prev_x - prev_y) * cos(dtr(iso_angle));
	*y = (prev_x + prev_y) * sin(dtr(iso_angle)) - z;
}

void	cavalier(double *x, double *y, double z)
{
	double prev_x;
	double prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = prev_x + z * 1 * cos(dtr(oblique_angle));
	*y = prev_y + z * 1 * sin(dtr(oblique_angle));
}

void	cabinet(double *x, double *y, double z)
{
	double prev_x;
	double prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = prev_x + z * 0.5 * cos(dtr(oblique_angle));
	*y = prev_y + z * 0.5 * sin(dtr(oblique_angle));
}

void	perspective(double *x, double *y, double *z)
{
	double prev_x;
	double prev_y;
	double d;

	prev_x = *x;
	prev_y = *y;
	d = 1 / (tan(dtr(90 / 2)));
	*x = prev_x / ((*z + 1) / d);
	*y = prev_y / ((*z + 1) / d);
	*z = d;
}
