/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voszadcs <voszadcs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 04:27:18 by ohamadou          #+#    #+#             */
/*   Updated: 2024/06/10 04:05:54 by voszadcs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <math.h>

void	game_loop(void *ml)
{
	t_game	*mlx;

	mlx = ml;
	mlx_delete_image(mlx->mlx, mlx->img);
	mlx->img = mlx_new_image(mlx->mlx, S_W, S_H);
	move_hook(mlx, 0, 0);
	cast_rays(mlx);
	mlx_image_to_window(mlx->mlx, mlx->img, 0, 0);
}


void init_the_player(t_game mlx)
{
	printf("Pos: %d %d", mlx.ply->player_x, mlx.ply->player_y);


	mlx.ply->player_x = (mlx.g_map->player_x * TILE_SIZE) + TILE_SIZE / 2;
	mlx.ply->player_y = (mlx.g_map->player_y * TILE_SIZE) + TILE_SIZE / 2;
	printf("POS: %d %d\n", mlx.ply->player_x, mlx.ply->player_y);

	mlx.ply->fov = (FOV * M_PI / 180);
	mlx.ply->p_angle = M_PI;
}

static void	load_texture(t_game *game)
{
	printf("Loading textures\n");
	game->tex->east = mlx_load_png(game->g_map->east);
	game->tex->south = mlx_load_png(game->g_map->south);
	game->tex->north = mlx_load_png(game->g_map->north);
	game->tex->west = mlx_load_png(game->g_map->west);
	if (!game->tex->east || !game->tex->south
		|| !game->tex->north || !game->tex->west)
	{
		free_game_struct(game);
		error(LOAD_TEXTURES);
	}
}

void	game_init(t_game *game)
{
	game->ply = malloc(sizeof(t_player));
	game->ray = malloc(sizeof(t_ray));
	game->tex = malloc(sizeof(t_texture));
	game->g_map = NULL;
	game->img = NULL;
	game->mlx = NULL;
	game->temp = NULL;
	game->tex->east = NULL;
	game->tex->west = NULL;
	game->tex->south = NULL;
	game->tex->north = NULL;
}

void	start_the_game(t_map *dt)
{
	t_game	game;

	game_init(&game);
	game.g_map = dt;
	game.mlx = mlx_init(S_W, S_H, "Cub3D", 0);
	load_texture(&game);


	init_the_player(game);
	printf("LEAVING PLAYER INIT\n");

	mlx_loop_hook(game.mlx, &game_loop, &game);
	mlx_key_hook(game.mlx, &mlx_key, &game);
	mlx_loop(game.mlx);
	mlx_close_window(game.mlx);
}
