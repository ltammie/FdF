#include "../includes/fdf.h"

void	rotate_x(double *y, double *z, t_mlx *data)
{
	double prev_y;

	prev_y = *y;
	*y = prev_y * data->cam.x_cos + *z * data->cam.x_sin;
	*z = -prev_y * data->cam.x_sin + *z * data->cam.x_cos;
}

void	rotate_y(double *x, double *z, t_mlx *data)
{
	double prev_x;

	prev_x = *x;
	*x = prev_x * data->cam.y_cos + *z * data->cam.y_sin;
	*z = -prev_x * data->cam.y_sin + *z * data->cam.y_cos;
}

void	rotate_z(double *x, double *y, t_mlx *data)
{
	double prev_x;
	double prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = prev_x * data->cam.z_cos - prev_y * data->cam.z_sin;
	*y = prev_x * data->cam.z_sin + prev_y * data->cam.z_cos;
}
