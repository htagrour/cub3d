#include "cub3d.h"

int  key_relased(int key, t_window *window)
{
    if (key == A || key == LEFT || key == D || key == RIGHT)
        window->rotate_direction = 0;
    if (key == S || key == W)
        window->walk_direction = 0;
    //update(window);
    return  (1);
}

int key_pressed(int key, t_window *window)
{
    if (key == S)
        window->walk_direction = -1;
    if (key == W)
        window->walk_direction = 1;
    if (key == D || key == RIGHT)
        window->rotate_direction = 1;
    if (key == A || key == LEFT)
        window->rotate_direction = -1;
    if (key == ESC)
    {
        mlx_destroy_window ( window->mlx_ptr, window->win_ptr);
        exit(0);
    }
    printf("re\n");
    //update(window);
    return (1);
}
int  update(t_window *window)
{
    t_coord start;
    free(window->img_ptr);
    //mlx_destroy_image(window->mlx_ptr, window->img_ptr);
    mlx_clear_window(window->mlx_ptr, window->win_ptr);
    window->img_ptr = mlx_new_image(window->mlx_ptr, WIN_WIDTH, WIN_HIGHET);
    window->img_data = (int*)mlx_get_data_addr(window->img_ptr, &window->bpp, &window->size_line, &window->endian);
    //clear windows
    /*changing postion of player*/
    window->angle +=  window->rotate_direction * ROTATION_SPEED;
    angle_adjust(&(window->angle));//adjus the rotation angle
    start.x = window->x + cos(window->angle) * SPEED * window->walk_direction;
    start.y = window->y + sin(window->angle) * SPEED * window->walk_direction;
    if (!is_there_wall((window->map), start.x, start.y))
    {
        window->x = start.x;
        window->y = start.y;
    }
    drawing_map(window);
    return (0);
}