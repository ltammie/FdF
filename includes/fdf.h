#ifndef FDF_FDF_H
# define FDF_FDF_H

# define WIDTH 2560
# define HEIGHT 1600
# define IMW 2260
# define IMH 1300
# define ISO_ANGLE 30.0
# define OBLIQUE_ANGLE 60.0

# include <math.h>
# include "../minilibx/mlx.h"
# include "../libft/includes/libft.h"
# include "keys.h"

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
	double		x;
	double		y;
	double		z;
	int			color;
}				t_point;

typedef struct	s_map
{
	int			mh;
	int			mw;
	int			x0;
	int			y0;
	t_point		*m;
}				t_map;

typedef struct	s_cam
{
	int			zoom;
	int			x_shift;
	int			y_shift;
	int			z_level;
	double		x_angle;
	double		y_angle;
	double		z_angle;
	double		x_sin;
	double		x_cos;
	double		y_sin;
	double		y_cos;
	double		z_sin;
	double		z_cos;
	char		proj;
}				t_cam;

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
	t_map		m;
	t_image		img;
	t_cam		cam;
}				t_mlx;

/*
** ----------start functions---------
*/

t_mlx			*start(void);
void			camera_init(t_mlx *data);
void			image_init(t_mlx *data);
void			read_map_data(char *filename, t_mlx *data);
void			camera_update(t_mlx *data);
void			draw_menu(t_mlx *d);

/*
** ----------drawing---------
*/

void			dda(t_mlx *data, t_point p1, t_point p2, int color);
void			draw_image(t_mlx *d);
void			draw_background(t_mlx *data);
void			rotate_x(double *y, double *z, t_mlx *data);
void			rotate_y(double *x, double *z, t_mlx *data);
void			rotate_z(double *x, double *y, t_mlx *data);
void			point_convert(t_mlx *data, t_point *p1, t_point *p2);
void			iso(double *x, double *y, double z);
void			cavalier(double *x, double *y, double z);
void			cabinet(double *x, double *y, double z);
void			perspective(double *x, double *y, double *z);
/*
** ----------controls----------
*/

int				move(int key, t_mlx *data);
int				zoom(int key, t_mlx *data);
int				rotate(int key, t_mlx *data);
int				flattening(int key, t_mlx *data);
void			close_fdf(t_mlx *data);

/*
** ----------other----------
*/

double			dtr(double degrees);
double			rtd(double radians);
void			errors(int err);
int				base(int c, int base);
int				ft_atoi_base(const char *str);

#endif
