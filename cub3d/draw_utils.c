/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 17:08:08 by htagrour          #+#    #+#             */
/*   Updated: 2020/01/27 08:57:14 by htagrour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*void    plot_circle (t_window window, int x, int y, int color)
{
   int dx;  II. Quadrant 
   int dy;
   int err;
   int tem;

   dx = -RADUIS;
   dy = 0;
   err = 2 - 2*RADUIS;
   while (dx < 0)
   {
       mlx_pixel_put(window.mlx_ptr, window.win_ptr, x - dx, y + dy, color);
       mlx_pixel_put(window.mlx_ptr, window.win_ptr, x - dy, y - dx, color);
       mlx_pixel_put(window.mlx_ptr, window.win_ptr, x + dx, y - dy, color);
       mlx_pixel_put(window.mlx_ptr, window.win_ptr, x + dy, y + dx, color);
      tem = err;
      if (tem > dx)
        err += ++dx * 2 + 1; 
      if (tem <= dy)
        err += ++dy * 2 + 1; 
   }
}*/

t_coord drawline(t_coord end_coord, t_window *window_, int color, int index)
{
    t_coord d_coord;
    t_coord w_coord;
    int errr;
    int e2;
    t_coord window;

    window.x = window_->x;
    window.y = window_->y;
    d_coord.x = abs(end_coord.x -window.x);
    w_coord.x = (window.x < end_coord.x) ? 1 : -1;
    d_coord.y = -abs(end_coord.y - window.y);
    w_coord.y = (window.y < end_coord.y) ? 1 : -1;
    errr = d_coord.x + d_coord.y;
    while (1)
    {
        if (index)
           window_->img_data[window.y * WIN_WIDTH + window.x] = color;
        if ((window.x == end_coord.x && window.y == end_coord.y && index) ||
                (is_there_wall(window_->map, window.x, window.y) && !index))
                {   
                        //window_->wall_inters = window;
                        return(window);//(window.x % TAILE) ? 1:0);
                }
        e2 = 2 * errr;
        if (e2 >= d_coord.y)
        {
            errr += d_coord.y;
            window.x += w_coord.x ;
        }
        if (e2 <= d_coord.x)
        {
            errr += d_coord.x;
            window.y += w_coord.y;
        }
    }
}

int draw_box(t_window *window, int index , t_coord coord, t_coord diment, int color)
{
    int x;
    int y;

    x = coord.x -1;
    while ( (++x < coord.x + diment.x))
    {
        y = coord.y - 1;
        while (++y < coord.y + diment.y)
        {   if (index == '1')  
                window->img_data[y * WIN_WIDTH + x] = color;
        }

    }
    return (1);
}