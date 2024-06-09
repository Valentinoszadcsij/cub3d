#ifndef CUB3D_H
# define CUB3D_H

# define PLAYER_WID 64
# define PLAYER_HEI 64
# define PLAYER_STEP 32

// ERROR CODES
# define WRONG_ARGS_NUM 1
# define NAME_LENGTH 2
# define WRONG_EXTENSION 3
# define FILE_OPEN 4
# define MAP_DESCRIPTION 5
# define INVALID_MAP 6
# define LOAD_TEXTURES 7
// misc
# define S_W 1900 // screen width
# define S_H 1000 // screen height
# define TILE_SIZE 15 // tile size
# define FOV 60 // field of view
# define ROTATION_SPEED 0.045 // rotation speed
# define PLAYER_SPEED 8	// player speed
# define M_PI 3.14159265358979323846


# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/libft.h"
# include "../src/get_next_line/get_next_line.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>

typedef struct s_map
{
	char *north;
	char *south;
	char *west;
	char *east;
	int *floor;
	int *ceiling;
	char **map2d;
    int map_w; // Map width
    int map_h; // Map height
    int player_x;
    int player_y;
}	t_map;

typedef struct s_tmp
{
	int id;
}	t_tmp;

typedef struct s_player {
    int player_x; // Player x position in pixels
    int player_y; // Player y position in pixels
    int direc_x;
    int direc_y;
    int rotation;
    double p_angle; // Player angle
    double p_speed; // Player speed
    float fov; // Field of view
} t_player;

typedef struct s_texture
{
	mlx_texture_t *north;
	mlx_texture_t *south;
	mlx_texture_t *west;
	mlx_texture_t *east;
} t_texture;

typedef struct s_ray	//the ray structure
{   
	int ray_i;
	double hor_x;
	double hor_y;
	double	ray_ngl;	// ray angle
	double	distance;	// distance to the wall
	int		flag;		// flag for the wall
	int hit_x;  // X-coordinate of the hit on the wall
    int hit_y;
    int is_vertical;
    t_texture *hit_tex;
}	t_ray;

typedef struct s_game	//the mlx structure
{
	mlx_t			*mlx;	// the mlx pointer
	mlx_image_t		*img;	// the image
	t_ray			*ray;	// the ray structure
	t_map			*g_map;	// the data structure
	t_player		*ply;	// the player structure
	t_texture       *tex;
	t_tmp           *temp;
}	t_game;

//parsing
char	    *get_next_line(int fd);
t_map		*parse(int argc, char **argv);
void        parse_description(t_map *map, char **input);
int         validate_descr(char **input);
int         is_rgb_value(char *str);
void        parse_map(t_map *map, char **input);
int         valid_map(char **map);
//general utils
int			error(int errnum);
void        free_double_char(char **array);
void        free_map_struct(t_map *map);
void        free_game_struct(t_game *game);
void        free_text_struct(t_texture *text);

void        start_the_game(t_map *map);

#endif