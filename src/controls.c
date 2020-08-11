#include "../includes/fdf.h"

int		move(int key, t_mlx *data)
{
	if (key == 123)
		data->cam.x_shift -= 10;
	if (key == 124)
		data->cam.x_shift += 10;
	if (key == 125)
		data->cam.y_shift += 10;
	if (key == 126)
		data->cam.y_shift -= 10;
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img.img_ptr);
	draw_image(data);
	return (0);
}

int		zoom(int key, t_mlx *data)
{
	if (key == 27)
	{
		if (data->cam.zoom != 1)
			data->cam.zoom--;
	}
	if (key == 24)
		data->cam.zoom++;
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img.img_ptr);
	draw_image(data);
	return (0);
}

int		rotate(int key, t_mlx *data)
{
	if (key == 0)
		data->cam.x_angle -= 10.0;
	if (key == 2)
		data->cam.x_angle += 10.0;
	if (key == 13)
		data->cam.y_angle += 10.0;
	if (key == 1)
		data->cam.y_angle -= 10.0;
	if (key == 12)
		data->cam.z_angle -= 10.0;
	if (key == 14)
		data->cam.z_angle += 10.0;
	if (fabs(data->cam.x_angle) >= 360.0)
		data->cam.x_angle = fabs(data->cam.x_angle) - (360.0);
	if (fabs(data->cam.y_angle) >= 360.0)
		data->cam.y_angle = fabs(data->cam.y_angle) - (360.0);
	if (fabs(data->cam.z_angle) >= 360.0)
		data->cam.z_angle = fabs(data->cam.z_angle) - (360.0);
	camera_update(data);
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img.img_ptr);
	draw_image(data);
	return (0);
}

int		flattening(int key, t_mlx *data)
{
	if (key == 15)
		data->cam.z_level += 1;
	if (key == 3)
		data->cam.z_level -= 1;
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img.img_ptr);
	draw_image(data);
	return (0);
}

void	close_fdf(t_mlx *data)
{
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img.img_ptr);
	(void)data;
	exit(0);
}
