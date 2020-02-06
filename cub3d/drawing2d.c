#include "cub3d.h"
t_ray ray[ARRAY_NUM];

void draw_walls_2d(t_window *window)
{
    t_coord coord;
    t_coord dimen;
    int j;
    int k;

    dimen.x = TAILE * SCALE;
    dimen.y = TAILE * SCALE;
    coord.x = 0;
    coord.y = 0;
    j = 0;
    while (j < MAP_NUM_ROWS)
    {   
        k = 0;
        while (k < MAP_NUM_COLS)
        {
            draw_box(window, window->map[j][k++], coord, dimen, 0x808080);
            coord.x += dimen.x;
        }
        coord.x = 0;
        coord.y += dimen.y;
        j++;
    }
}
int    *draw_arrays(t_window *window)
{
    int i;

    i  = 0;
    ray[i].angle = window->angle - FOV / 2;
    while (i < ARRAY_NUM)
    {
        angle_adjust(&ray[i].angle);
        inter_dist(*window,&ray[i]);
        ray[i + 1].angle = ray[i].angle + FOV / ARRAY_NUM;
        i++;
    }
    return (0);
}
void draw_line1(t_window *window)
{
    int i = -1;
    while (++i < ARRAY_NUM)
    {
        ray[i].insters.x = floor(ray[i].insters.x * SCALE);
        ray[i].insters.y = floor(ray[i].insters.y * SCALE);
        drawline(ray[i].insters, window, 0xff0000);
    }
}

void draw_walls_3d(t_window *window)
{
    int i;
    double corr_dis;
    double projec_dis;
    int wall_hieght;
    t_coord p;
    t_coord d;
    i = -1;
    while (++i < ARRAY_NUM)
    {
        corr_dis = ray[i].dist * cos(ray[i].angle - window->angle);
        projec_dis = (WIN_WIDTH / 2) / tan(FOV / 2);
        wall_hieght = (TAILE / ray[i].dist) * projec_dis;
        p.x = i * 1;
        p.y =  floor((WIN_HIGHET / 2) - (wall_hieght / 2));
        d.x = 1;
        d.y = floor(wall_hieght);
        draw_box(window, '1', p, d, 0xffffff);
    }
}
void drawing_map(t_window *window)
{
    draw_walls_2d(window);
    draw_arrays(window);
    //draw_walls_3d(window);
    draw_line1(window);
    mlx_put_image_to_window(window->mlx_ptr, window->win_ptr, window->img_ptr, 0, 0);
}
