#include "../includes/fdf.h"

static	void	zoom_points(t_mlx *data, t_point *p1, t_point *p2)
{
	(*p1).x *= data->cam.zoom;
	(*p1).y *= data->cam.zoom;
	(*p1).z *= data->cam.z_level;
	(*p2).x *= data->cam.zoom;
	(*p2).y *= data->cam.zoom;
	(*p2).z *= data->cam.z_level;
}

static	void	rotate_points(t_mlx *data, t_point *p1, t_point *p2)
{
	rotate_x(&p1->y, &p1->z, data);
	rotate_x(&p2->y, &p2->z, data);
	rotate_y(&p1->x, &p1->z, data);
	rotate_y(&p2->x, &p2->z, data);
	rotate_z(&p1->x, &p1->y, data);
	rotate_z(&p2->x, &p2->y, data);
}

static	void	shift_points(t_mlx *data, t_point *p1, t_point *p2)
{
	p1->x += (float)IMW / 2.0f;
	p1->y += (float)IMH / 2.0f;
	p2->x += (float)IMW / 2.0f;
	p2->y += (float)IMH / 2.0f;
	p1->x += data->cam.x_shift;
	p1->y += data->cam.y_shift;
	p2->x += data->cam.x_shift;
	p2->y += data->cam.y_shift;
}

void			point_convert(t_mlx *data, t_point *p1, t_point *p2)
{
	zoom_points(data, p1, p2);
	rotate_points(data, p1, p2);
	if (data->cam.proj == 'I')
	{
		iso(&p1->x, &p1->y, p1->z);
		iso(&p2->x, &p2->y, p2->z);
	}
	shift_points(data, p1, p2);
}
