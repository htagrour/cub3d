#include "cub3d.h"

void    plot_circle (int r, t_comp com)
{
   int x = -r, y = 0, err = 2-2*r; /* II. Quadrant */ 
   while (x < 0)
   {
       mlx_pixel_put(com.mlx_ptr, com.win_ptr, com.player_x - x, com.player_y + y, 0xffffff);
       mlx_pixel_put(com.mlx_ptr, com.win_ptr, com.player_x - y, com.player_y - x, 0xffffff);
       mlx_pixel_put(com.mlx_ptr, com.win_ptr, com.player_x + x, com.player_y - y, 0xffffff);
       mlx_pixel_put(com.mlx_ptr, com.win_ptr, com.player_x + y, com.player_y + x, 0xffffff);
      r = err;
      if (r >  x)
        err += ++x*2+1; /* e_xy+e_x > 0 */
      if (r <= y)
        err += ++y*2+1; /* e_xy+e_y < 0 */
   }
}

int draw_box(t_comp com, int index , t_coord coord)
{
    int x;
    int y;

    x = coord.x -1;
    while ( (++x < coord.x + 20))
    {
        y = coord.y - 1;
        while (++y < coord.y + 20)
        {   if (index == '1')  
            mlx_pixel_put(com.mlx_ptr, com.win_ptr, x, y, 0xffffff);
        }

    }
    return (1);
}

/*Bresenham Line Drawing Algorithm*/

void drawline(int x0, int y0, int x1, int y1, t_comp com)
{
    int dx;
    int dy;
    int sx;
    int sy;
    int errr;
    int e2;
    int color;

    color = (int)0x00ff00;
    dx = abs(x1 -x0);
    sx = (x0 < x1) ? 1 : -1;
    dy = -abs(y1 - y0);
    sy = (y0 < y1) ? 1 : -1;
    errr = dx + dy;
    while (1)
    {
        mlx_pixel_put(com.mlx_ptr, com.win_ptr, x0, y0, color);
        if ((x0 == x1 && y0 == y1) || is_there_wall(com.map, x0, y0))
            break;
        e2 = 2 * errr;
        if (e2 >= dy)
        {
            errr += dy;
            x0 += sx;
        }
        if (e2 <= dx)
        {
            errr += dx;
            y0 += sy;
        }
    }
}
void draw_arrays(t_comp com)
{
    int end_x;
    int end_y;
    double angle;
    int array_num;
    int i;
    double fov = PI / 3;
    int width = 48 * 20;
    array_num = width; // width
    i = -1;
    angle = com.angle - fov / 2; // player.angle - fov / 2
    while (++i < array_num)
    {
        end_x = com.player_x + cos(angle) * 100;
        end_y = com.player_y + sin(angle) * 100;
        drawline(com.player_x, com.player_y, end_x, end_y, com);
        angle += fov / array_num;// fov/width
    }
}
int draw_line(t_comp *com)
{
    int end_x;
    int end_y;
    int line_taill;

    line_taill = 100;
    end_x = com->player_x + cos(com->angle) * line_taill;
    end_y = com->player_y + sin(com->angle) * line_taill;
    drawline(com->player_x, com->player_y, end_x, end_y, *com);
    draw_arrays(*com);
    com->rotate_direction = 0;
    com->walk_direction = 0;
    return (1);
}

int draw_player(t_comp *com)
{
    draw_line(com);
    plot_circle(5, *com);
	return (1);

}

void drawing_map(t_comp *com)
{
    t_coord coord;
    int j;
    int k;

    coord.x = 0;
    coord.y = 0;
    j = 0;
    while (com->map[j])
    {   
        k = 0;
        while (com->map[j][k])
        {
            draw_box(*com, com->map[j][k++], coord);
            coord.x += 20;
        }
        coord.x = 0;
        coord.y += 20;
        j++;
    }
	draw_player(com); 
    printf("%d|%d|%d|%d|%c\n" , com->player_x, com->player_y,com->player_x / 20,
    com->player_y / 20, com->map[(com->player_y) / 20][(com->player_x)/ 20]);
}
