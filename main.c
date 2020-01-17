/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltammie <ltammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 16:33:12 by ltammie           #+#    #+#             */
/*   Updated: 2020/01/17 05:48:45 by sauron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"
#include <stdio.h>

int 	deal_key(int key, t_mlx *data)
{
//	ft_putnbr(key);
//	ft_putchar('\n');
	if (key == 123 || key == 124 || key == 125 || key == 126)
		move(key, data);
	else if (key == 27 || key == 24)
		zoom(key, data);
	else if (key == 0 || key == 1 || key == 2 || key == 12 || key == 13 || key == 14)
		rotate(key, data);
	else if (key == 15 || key == 3)
		flattening(key, data);
	else if (key == 53)
		close_fdf(key, data);
	return (0);
}

void	suicide(char *error_text)
{
	ft_putstr(error_text);
	exit(0);
}

int		main(int argc, char **argv)
{
	t_mlx	*data;

	if (argc != 2)
		suicide(ERR_ARGV);
	data = start();
	read_map_data(argv[1], data);
	printf("x0 = %d\ny0 = %d\n", data->map.x0, data->map.y0);
	draw_image(data);
	mlx_key_hook(data->window, deal_key, data);
	mlx_loop(data->mlx);
	return (0);
}
