#include "../includes/fdf.h"

static	void	set_pixel(int x, int y, t_mlx *data, int color)
{
	if (x >= 0 && x < IMW && y >= 0 && y < IMH)
		data->img.img_data[y * IMW + x] = color;
}

void			dda(t_mlx *data, t_point p1, t_point p2, int color)
{
	double	dx;
	double	dy;
	double	max;

	point_convert(data, &p1, &p2);
	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	max = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
	dx = dx / max;
	dy = dy / max;
	while ((int)(p1.x - p2.x) || (int)(p1.y - p2.y))
	{
		set_pixel((int)p1.x, (int)p1.y, data, color);
		p1.x += dx;
		p1.y += dy;
	}
}
