#include "cub3d.h"

int print_key(int key , void *l)
{
    printf("%d|%d\n", key, (int)l);
    return(1);
}
int main()
{
    t_comp com;
    int win_width;
    int win_hieght;

    com.speed = 10;
    com.angle = 0;
    com.player_x = 100;
    com.player_y = 100;
    com.rotate_direction = 0;

    win_hieght = 900;
    win_width = 1700;
    com.mlx_ptr = mlx_init();
    com.win_ptr = mlx_new_window( com.mlx_ptr, win_width, win_hieght, "hello wolrd");
    extract_map(&com);
    drawing_map(&com);
    mlx_hook(com.win_ptr, 2, 0, update, &com);
    //mlx_mouse_hook(com.win_ptr, update_x, &com);
    mlx_loop(com.mlx_ptr);
    return (0);
}


//a = 0;
//w = 13;
//s = 1;
//d = 2;
//esc = 53;
//left = 123;
//right = 124