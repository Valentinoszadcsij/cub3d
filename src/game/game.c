#include "../../include/cub3d.h"

// game structure containing most of game data
game_t  *game_init(mlx_t *mlx, player_t *player)
{
    game_t *game;

    game = malloc(sizeof(game_t));
    game->mlx = mlx;
    game->player = player;
    return (game);
}

// main game loop
void game_loop(void *param)
{
    game_t *game = param;
    player_move(game->mlx, game->player);
}
