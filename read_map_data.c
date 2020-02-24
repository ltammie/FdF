/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sauron <sauron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 02:38:13 by sauron            #+#    #+#             */
/*   Updated: 2020/02/24 19:21:06 by ltammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

static	void	get_mh_mw(int fd, t_mlx *data)
{
	char	*line;

	data->m.mH = 0;
	data->m.mW = 0;
	while (get_next_line(fd, &line))
	{
		data->m.mW = ft_count_words(line, ' ');
		data->m.mH++;
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
		data->m.m[j * data->m.mW + i].x = i;
		data->m.m[j * data->m.mW + i].y = j;
		data->m.m[j * data->m.mW + i].z = ft_atoi(strarr[i]);
		if (ft_strchr(strarr[i], ','))
			data->m.m[j * data->m.mW + i].color = ft_atoi_base(ft_strchr(strarr[i], ',') + 1);
		else if (data->m.m[j * data->m.mW + i].z == 0)
			data->m.m[j * data->m.mW + i].color = 0xd2691e;
		else if (data->m.m[j * data->m.mW + i].z > 0)
			data->m.m[j * data->m.mW + i].color = 0xbebebe;
		else if (data->m.m[j * data->m.mW + i].z < 0)
			data->m.m[j * data->m.mW + i].color = 0x1e90ff;
		i++;
	}
}

static	void	make_grid(int fd, t_mlx *data)
{
	int		j;
	char	*line;
	char	**temp;

	if (!(data->m.m = (t_point *)malloc(sizeof(t_point)
			* data->m.mH * data->m.mW)))
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
	data->m.x0 = data->m.mW / 2;
	data->m.y0 = data->m.mH / 2;
	while (i < data->m.mH)
	{
		j = 0;
		while (j < data->m.mW)
		{
			data->m.m[i * data->m.mW + j].x -= data->m.x0;
			data->m.m[i * data->m.mW + j].y -= data->m.y0;
			j++;
		}
		i++;
	}
}
