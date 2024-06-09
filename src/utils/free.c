#include "../../include/cub3d.h"

void    free_double_char(char **array)
{
    char    **copy;

    copy = array;
    while (*copy)
    {
        free(*copy);
        copy++;
    }
    free(array);
}

void    free_map_struct(t_map *map)
{
    if (map->north)
        free(map->north);
    if (map->south)
        free(map->south);
    if (map->west)
        free(map->west);
    if (map->east)
        free(map->east);
    if (map->ceiling)
        free(map->ceiling);
    if (map->floor)
        free(map->floor);
    if (map->map2d)
        free_double_char(map->map2d);
    free(map);
}

void    free_text_struct(t_texture *text)
{
    if (text->south)
        free(text->south);
    if (text->north)
        free(text->north);
    if (text->east)
        free(text->east);
    if (text->west)
        free(text->west);
    free(text);
}

void    free_game_struct(t_game *game)
{
    if (game->g_map)
        free_map_struct(game->g_map);
    if (game->tex)
        free_text_struct(game->tex);
}