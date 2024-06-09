#include "../../include/cub3d.h"

player_t *player_init(int x, int y, int direction, mlx_t *mlx)
{
    player_t    *player;

    player = malloc(sizeof(player_t));
    player->px = x;
    player->py = y;
    player->pd = direction;
    player->p_img = mlx_new_image(mlx, PLAYER_WID, PLAYER_HEI);
    memset(player->p_img->pixels, 255, PLAYER_HEI * PLAYER_WID * 4);
    return(player);
}

void    player_move(mlx_t *mlx, player_t *player)
{
        // player->p_img->instances[0].y += PLAYER_STEP;
 
    if (mlx_is_key_down(mlx, MLX_KEY_W))
        printf("W pressed\n");
    else if (mlx_is_key_down(mlx, MLX_KEY_S))
        player->p_img->instances[0].y -= PLAYER_STEP;
    else if (mlx_is_key_down(mlx, MLX_KEY_D))
        player->p_img->instances[0].x += PLAYER_STEP;
    else if (mlx_is_key_down(mlx, MLX_KEY_A))
        player->p_img->instances[0].x -= PLAYER_STEP;
}