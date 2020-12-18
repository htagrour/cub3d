/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 08:22:23 by htagrour          #+#    #+#             */
/*   Updated: 2020/02/26 16:44:19 by htagrour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		key_relased(int key, t_window *window)
{
	if (key == A || key == LEFT || key == D || key == RIGHT)
		window->rotate_direction = 0;
	if (key == S || key == W)
		window->walk_direction = 0;
	return (1);
}

int		key_pressed(int key, t_window *window)
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
		mlx_destroy_window(window->mlx_ptr, window->win_ptr);
		ft_exit(window);
	}
	return (1);
}

void	update(t_window *win)
{
	t_coord start;

	mlx_destroy_image(win->mlx_ptr, win->img_ptr);
	mlx_clear_window(win->mlx_ptr, win->win_ptr);
	win->img_ptr = mlx_new_image(win->mlx_ptr, win->width, win->hight);
	win->img_data = (int*)mlx_get_data_addr(win->img_ptr, &win->bpp,
					&win->size_line, &win->endian);
	win->angle += win->rotate_direction * ROTATION_SPEED;
	angle_adjust(&(win->angle));
	start.x = win->p.x + cos(win->angle) * SPEED * win->walk_direction;
	start.y = win->p.y + sin(win->angle) * SPEED * win->walk_direction;
	if (!is_there_wall(*win, start.x, start.y))
	{
		win->p.x = floor(start.x);
		win->p.y = floor(start.y);
	}
	drawing_scene(win);
}
