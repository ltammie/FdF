/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltammie <ltammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 20:10:01 by ltammie           #+#    #+#             */
/*   Updated: 2020/02/24 20:54:12 by ltammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

static	void	get_mh_mw(int fd, t_mlx *data)
{
	char	*line;

	data->m.mh = 0;
	data->m.mw = 0;
	line = NULL;
	while (get_next_line(fd, &line))
	{
		if (!data->m.mw)
			data->m.mw = ft_count_words(line, ' ');
		if (data->m.mw != ft_count_words(line, ' '))
			errors(2);
		data->m.mh++;
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
		data->m.m[j * data->m.mw + i].x = i;
		data->m.m[j * data->m.mw + i].y = j;
		data->m.m[j * data->m.mw + i].z = ft_atoi(strarr[i]);
		if (ft_strchr(strarr[i], ','))
			data->m.m[j * data->m.mw + i].color =
					ft_atoi_base(ft_strchr(strarr[i], ',') + 1);
		else if (data->m.m[j * data->m.mw + i].z == 0)
			data->m.m[j * data->m.mw + i].color = 0xd2691e;
		else if (data->m.m[j * data->m.mw + i].z > 0)
			data->m.m[j * data->m.mw + i].color = 0xbebebe;
		else if (data->m.m[j * data->m.mw + i].z < 0)
			data->m.m[j * data->m.mw + i].color = 0x1e90ff;
		free(strarr[i]);
		i++;
	}
}

static	void	make_grid(int fd, t_mlx *data)
{
	int		j;
	char	*line;
	char	**temp;

	if (!(data->m.m = (t_point *)malloc(sizeof(t_point)
										* data->m.mh * data->m.mw)))
		errors(0);
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
	int		fd;
	int		i;
	int		j;
	char	*line;

	i = 0;
	line = NULL;
	if (((fd = open(filename, O_RDONLY)) < 0) || ((read(fd, line, 0)) < 0))
		errors(1);
	get_mh_mw(fd, data);
	make_grid(fd = open(filename, O_RDONLY), data);
	data->m.x0 = data->m.mw / 2;
	data->m.y0 = data->m.mh / 2;
	while (i < data->m.mh)
	{
		j = 0;
		while (j < data->m.mw)
		{
			data->m.m[i * data->m.mw + j].x -= data->m.x0;
			data->m.m[i * data->m.mw + j].y -= data->m.y0;
			j++;
		}
		i++;
	}
}
