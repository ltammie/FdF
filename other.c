/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltammie <ltammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:48:07 by ltammie           #+#    #+#             */
/*   Updated: 2020/01/28 16:01:28 by ltammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

float	degToRad(float degrees)
{
	return ((degrees) * M_PI / 180);
}

float	radToDeg(float radians)
{
	return ((radians) * 180 / M_PI);
}

void	suicide(char *error_text)
{
	ft_putstr(error_text);
	exit(0);
}
