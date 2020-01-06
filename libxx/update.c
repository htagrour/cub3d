#include "cub3d.h"

int update(int key, t_comp *com)
{
    int start_x;
    int start_y;

    if (key == 1)
        com->walk_direction = -1;
    if (key == 13)
        com->walk_direction = 1;
    if (key == 2 || key == 123)
        com->rotate_direction = 1;
    if (key == 0 || key == 124)
        com->rotate_direction = -1;
    if (key == 53)
    {
        mlx_destroy_window ( com->mlx_ptr, com->win_ptr);
        exit(0);
    }
    mlx_clear_window(com->mlx_ptr, com->win_ptr);
    com->angle +=  com->rotate_direction * (PI / 10);
    start_x = com->player_x + cos(com->angle) * com->speed * com->walk_direction;
    start_y = com->player_y + sin(com->angle) * com->speed * com->walk_direction;
    if (!is_there_wall((com->map), start_x, start_y))
    {
        com->player_x = start_x;
        com->player_y = start_y;
    }
    drawing_map(com);
	return (0);
}

/*int update_x(int key, int x, int y, t_comp *com)
{
    if (key)
    {
        com->player_x = x;
        com->player_y = y;
        mlx_clear_window(com->mlx_ptr, com->win_ptr);
        drawing_map(com);
    }
	return (0);
}*/