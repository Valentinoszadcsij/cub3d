#include "../../include/cub3d.h"

int	unit_circle(float angle, char c)
{
	if (c == 'x')
	{
		if (angle > 0 && angle < M_PI)
			return (1);
	}
	else if (c == 'y')
	{
		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
			return (1);
	}
	return (0);
}

int	inter_check(float angle, float *inter, float *step, int is_horizon)
{
	if (is_horizon)
	{
		if (angle > 0 && angle < M_PI)
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2))
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

int	wall_hit(float x, float y, t_game *mlx)
{
	int	x_m;
	int	y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor(x / TILE_SIZE);
	y_m = floor(y / TILE_SIZE);
	if ((y_m >= mlx->g_map->map_h || x_m >= mlx->g_map->map_w))
		return (0);
	if (mlx->g_map->map2d[y_m] && x_m <= (int)strlen(mlx->g_map->map2d[y_m]))
	{
		if (mlx->g_map->map2d[y_m][x_m] == '1')
			return (0);
		else
			return (1);
	}
	return (1);
}

float	get_h_inter(t_game *mlx, float angl)
{
	float	h_x;
	float	h_y;
	float	x_step;
	float	y_step;
	int		pixel;

	y_step = TILE_SIZE;
	x_step = TILE_SIZE / tan(angl);
	h_y = floor(mlx->ply->player_y / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angl, &h_y, &y_step, 1);
	h_x = mlx->ply->player_x + (h_y - mlx->ply->player_y) / tan(angl);
	if ((unit_circle(angl, 'y') && x_step > 0) || \
		(!unit_circle(angl, 'y') && x_step < 0))
		x_step *= -1;
	while (wall_hit(h_x, h_y - pixel, mlx))
	{
		h_x += x_step;
		h_y += y_step;
	}
	mlx->ray->hor_x = h_x;
	mlx->ray->hor_y = h_y;
	return (sqrt(pow(h_x - mlx->ply->player_x, 2) + \
	pow(h_y - mlx->ply->player_y, 2)) + 0.00001);
}

float	get_v_inter(t_game *mlx, float angl)
{
	float	v_x;
	float	v_y;
	float	x_step;
	float	y_step;
	int		pixel;

	x_step = TILE_SIZE;
	y_step = TILE_SIZE * tan(angl);
	v_x = floor(mlx->ply->player_x / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angl, &v_x, &x_step, 0);
	v_y = mlx->ply->player_y + (v_x - mlx->ply->player_x) * tan(angl);
	if ((unit_circle(angl, 'x') && y_step < 0) || \
	(!unit_circle(angl, 'x') && y_step > 0))
		y_step *= -1;
	while (wall_hit(v_x - pixel, v_y, mlx))
	{
		v_x += x_step;
		v_y += y_step;
	}
	mlx->ray->hor_x = v_x;
	mlx->ray->hor_y = v_y;
	return (sqrt(pow(v_x - mlx->ply->player_x, 2) + \
	pow(v_y - mlx->ply->player_y, 2)));
}

void	cast_rays(t_game *mlx)
{
	double	h_inter;
	double	v_inter;
	int		ray;

	ray = 0;
	mlx->ray->ray_ngl = mlx->ply->p_angle - (mlx->ply->fov / 2);
	while (ray <= S_W)
	{
		mlx->ray->flag = 0;
		h_inter = get_h_inter(mlx, nor_angle(mlx->ray->ray_ngl));
		v_inter = get_v_inter(mlx, nor_angle(mlx->ray->ray_ngl));
		if (v_inter <= h_inter)
			mlx->ray->distance = v_inter;
		else
		{
			mlx->ray->distance = h_inter;
			mlx->ray->flag = 1;
		}
		render_wall(mlx, ray);
		ray++;
		mlx->ray->ray_ngl += (mlx->ply->fov / S_W);
	}
}

// void cast_rays(t_game *mlx) {
//     double h_inter;
//     double v_inter;
//     int ray;

//     ray = 0;
//     mlx->ray->ray_ngl = nor_angle(mlx->ply->p_angle - (mlx->ply->fov / 2));
//     while (ray < S_W) {
//         mlx->ray->flag = 0;
//         h_inter = get_h_inter(mlx, nor_angle(mlx->ray->ray_ngl));
//         v_inter = get_v_inter(mlx, nor_angle(mlx->ray->ray_ngl));
//         if (v_inter <= h_inter) {
//             mlx->ray->distance = v_inter;
//             mlx->ray->is_vertical = 1;
//         } else {
//             mlx->ray->distance = h_inter;
//             mlx->ray->is_vertical = 0;
//         }
//         render_wall(mlx, ray);
//         ray++;
//         mlx->ray->ray_ngl += (mlx->ply->fov / S_W);
//     }
// }
