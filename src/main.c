#include "../include/cub3d.h"

// Bytes Per Pixel. Since each pixel is represented as an integer, it will be four bytes for four channels.
#define BPP sizeof(int32_t)
#define UNIT 64

int	mmain(int argc, char **argv)
{
	t_map	*map;
    map = parse(argc, argv);
    // while (*map->map2d)
    // {   
    //     printf("Line: %s\n", *map->map2d);
    //     map->map2d++;
    // }
	start_the_game(map);

    return (EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
	mmain(argc, argv);
	system("leaks a.out");
}