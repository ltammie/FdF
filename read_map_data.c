/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sauron <sauron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 02:38:13 by sauron            #+#    #+#             */
/*   Updated: 2020/02/01 04:29:27 by sauron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

static void	get_mH_mW(int fd, t_mlx *data)
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

static void strArr_to_pointsArr(char **strArr, t_mlx *data, int j)
{
	int i;

	i = 0;
	while (strArr[i] != '\0')
	{
		data->map.grid[j * data->map.mW + i].x = i;
		data->map.grid[j * data->map.mW + i].y = j;
		data->map.grid[j * data->map.mW + i].z= ft_atoi(strArr[i]);

		i++;
	}
}

static void make_grid(int fd, t_mlx *data)
{
	int		j;
	char	*line;
	char 	**temp;

	if (!(data->map.grid = (t_point *)malloc(sizeof(t_point) * data->map.mH * data->map.mW)))
		suicide(ERR_MALLOC);
	j = 0;
	while (get_next_line(fd, &line))
	{
		temp = ft_strsplit(line, ' ');
		strArr_to_pointsArr(temp, data, j);
		free(temp);
		free(line);
		j++;
	}
	close(fd);
}

void		read_map_data(char *filename, t_mlx *data)
{
	int fd;
	int i;
	int j;

	i = 0;
	get_mH_mW(fd = open(filename, O_RDONLY), data);
	make_grid(fd = open(filename, O_RDONLY), data);
	data->map.x0 = data->map.mW / 2;
	data->map.y0 = data->map.mH / 2;
	while (i < data->map.mH)
	{
		j = 0;
		while (j < data->map.mW)
		{
			data->map.grid[i * data->map.mW + j].x -= data->map.x0;
			data->map.grid[i * data->map.mW + j].y -= data->map.y0;
			j++;
		}
		i++;
	}
}
