/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sauron <sauron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 02:38:13 by sauron            #+#    #+#             */
/*   Updated: 2020/02/24 17:23:47 by ltammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

static	void	get_mh_mw(int fd, t_mlx *data)
{
	char	*line;

	data->map.mH = 0;
	data->map.mW = 0;
	while (get_next_line(fd, &line))
	{
		data->map.mW = ft_count_words(line, ' ');
		data->map.mH++;
		free(line);
	}
	close(fd);
}

static	void	to_points(char **strarr, t_mlx *data, int j)
{
	int i;

	i = 0;
	while (strarr[i] != '\0')
	{
		data->map.m[j * data->map.mW + i].x = i;
		data->map.m[j * data->map.mW + i].y = j;
		data->map.m[j * data->map.mW + i].z = ft_atoi(strarr[i]);
		i++;
	}
}

static	void	make_grid(int fd, t_mlx *data)
{
	int		j;
	char	*line;
	char	**temp;

	if (!(data->map.m = (t_point *)malloc(sizeof(t_point)
										  * data->map.mH * data->map.mW)))
		suicide(ERR_MALLOC);
	j = 0;
	while (get_next_line(fd, &line))
	{
		temp = ft_strsplit(line, ' ');
		to_points(temp, data, j);
		free(temp);
		free(line);
		j++;
	}
	close(fd);
}

void			read_map_data(char *filename, t_mlx *data)
{
	int fd;
	int i;
	int j;

	i = 0;
	get_mh_mw(fd = open(filename, O_RDONLY), data);
	make_grid(fd = open(filename, O_RDONLY), data);
	data->map.x0 = data->map.mW / 2;
	data->map.y0 = data->map.mH / 2;
	while (i < data->map.mH)
	{
		j = 0;
		while (j < data->map.mW)
		{
			data->map.m[i * data->map.mW + j].x -= data->map.x0;
			data->map.m[i * data->map.mW + j].y -= data->map.y0;
			j++;
		}
		i++;
	}
}
