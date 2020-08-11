#include "../includes/fdf.h"

void	image_init(t_mlx *data)
{
	data->img.img_ptr = mlx_new_image(data->mlx, IMW, IMH);
	data->img.img_data = (int *)mlx_get_data_addr(data->img.img_ptr,
			&data->img.bpp, &data->img.size_l, &data->img.endian);
	draw_background(data);
}

void	camera_update(t_mlx *data)
{
	data->cam.x_sin = sin(dtr(data->cam.x_angle));
	data->cam.x_cos = cos(dtr(data->cam.x_angle));
	data->cam.y_sin = sin(dtr(data->cam.y_angle));
	data->cam.y_cos = cos(dtr(data->cam.y_angle));
	data->cam.z_sin = sin(dtr(data->cam.z_angle));
	data->cam.z_cos = cos(dtr(data->cam.z_angle));
}

void	camera_init(t_mlx *data)
{
	data->cam.zoom = 30;
	data->cam.x_shift = 0;
	data->cam.y_shift = 0;
	data->cam.z_level = 1;
	data->cam.x_angle = 0;
	data->cam.y_angle = 0;
	data->cam.z_angle = 0;
	camera_update(data);
}

void	draw_menu(t_mlx *d)
{
	mlx_string_put(d->mlx, d->win, 50, 50, 0xff0000, "Move image by arrows");
	mlx_string_put(d->mlx, d->win, 50, 90, 0xff0000, "X-Rotation by A and D");
	mlx_string_put(d->mlx, d->win, 50, 140, 0xff0000, "Y-Rotation by W and S");
	mlx_string_put(d->mlx, d->win, 50, 180, 0xff0000, "Z-Rotation by Q and E");
	mlx_string_put(d->mlx, d->win, 50, 220, 0xff0000, "Zoom using - and +");
	mlx_string_put(d->mlx, d->win, 50, 260, 0xff0000, "Change Z by R and F");
	mlx_string_put(d->mlx, d->win, 50, 300, 0xff0000, "Swap projections by P");
	mlx_string_put(d->mlx, d->win, 50, 340, 0xff0000, "Press ESC to exit");
}

t_mlx	*start(void)
{
	t_mlx *data;

	if (!(data = (t_mlx *)malloc(sizeof(t_mlx))))
		errors(0);
	if (!(data->mlx = mlx_init()))
		errors(0);
	if (!(data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "fdf")))
		errors(0);
	camera_init(data);
	data->cam.proj = 'I';
	return (data);
}
