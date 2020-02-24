/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltammie <ltammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 18:55:58 by ltammie           #+#    #+#             */
/*   Updated: 2020/02/01 04:39:39 by sauron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_FDF_H
#define FDF_FDF_H

//# define WIDTH 2560
//# define HEIGHT 1600
//# define imW 2560
//# define imH 1600
# define WIDTH 1024
# define HEIGHT 640
# define imW 1024
# define imH 640
# define iso_angle 30.0
# define oblique_angle 60.0

#include <math.h>
#include "../minilibx/mlx.h"
#include "../libft/libft.h"
#include "errors.h"
#include "keys.h"

typedef struct	s_image
{
	void		*img_ptr;
	int			*img_data;
	int			size_l;
	int			bpp;
	int			endian;
}				t_image;

typedef struct	s_point
{
	double 		x;
	double 		y;
	double		z;
	int 		color;
}				t_point;

typedef struct	s_map
{
	int 		mH;
	int 		mW;
	int 		x0;
	int 		y0;
	t_point		*grid;
}				t_map;

typedef struct	s_cam
{
	int			zoom;
	int			x_shift;
	int 		y_shift;
	int 		z_level;
	double		x_angle;
	double 		y_angle;
	double		z_angle;
	char 		projection;
}				t_cam;

typedef struct	s_mlx
{
	void		*mlx;
	void		*window;
	t_map		map;
	t_image		image;
	t_cam		cam;
}				t_mlx;

/*
 ** ----------start functions---------
 */

t_mlx			*start();
void			camera_init(t_mlx *data);
void			read_map_data(char *filename, t_mlx *data);

/*
 ** ----------drawing---------
 */

void			dda(t_mlx *data, t_point p1, t_point p2);
void			draw_image(t_mlx *data);
void			iso(double *x, double *y, int z);
void			cavalier(double *x, double *y, int z);
void			cabinet(double *x, double *y, int z);
void			perspective(double *x, double *y, double *z);
/*
 ** ----------controls----------
 */

int				move(int key, t_mlx *data);
int				zoom(int key, t_mlx *data);
int				rotate(int key, t_mlx *data);
int 			flattening(int key, t_mlx *data);
void			close_fdf(t_mlx *data);

/*
 ** ----------other----------
 */

float			dtr(float degrees);
float			rtd(float radians);
void			suicide(char *error_text);

#endif
