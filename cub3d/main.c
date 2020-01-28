/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 14:57:29 by htagrour          #+#    #+#             */
/*   Updated: 2020/01/28 01:00:58 by htagrour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <string.h>

int a = 0;
int update1(t_window *window)
{
   // mlx_destroy_image(window->mlx_ptr, window->img_ptr);
    mlx_clear_window(window->mlx_ptr, window->win_ptr);
    window->img_ptr = mlx_new_image(window->mlx_ptr, WIN_WIDTH, WIN_HIGHET);
    mlx_hook(window->win_ptr, 2, 0, key_pressed, window);
    mlx_hook(window->win_ptr, 3, 0, key_relased, window);
    update(window);
    printf("%d\n", a++);
    drawing_map(window);
    return (0);
}
int main()
{
    t_window window;
//TODO: you have a problem in scale and 3d map find it !!!
    init_var(&window);
    extract_map(&window);
    window.mlx_ptr = mlx_init();
    window.win_ptr = mlx_new_window( window.mlx_ptr, WIN_WIDTH, WIN_HIGHET, "CUB3D");
    window.img_ptr = mlx_new_image(window.mlx_ptr, WIN_WIDTH, WIN_HIGHET);
    window.img_data = (int*)mlx_get_data_addr(window.img_ptr, &window.bpp, &window.size_line, &window.endian);
    drawing_map(&window);
    mlx_hook(window.win_ptr, 2, 0, key_pressed, &window);
    mlx_hook(window.win_ptr, 3, 0, key_relased, &window);
    mlx_loop_hook(window.win_ptr, &update, &window);
    
    mlx_loop(window.mlx_ptr);
    return (0);
}