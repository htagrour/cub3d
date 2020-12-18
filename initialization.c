/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 04:34:04 by htagrour          #+#    #+#             */
/*   Updated: 2020/03/11 07:46:36 by htagrour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		g_j;
int		g_widht;
int		g_hight;

void		get_texture(t_window *win, int i, char c)
{
	if (c == 'N')
		win->texture_ptr = mlx_xpm_file_to_image(win->mlx_ptr, win->no_texture,
												&g_widht, &g_hight);
	if (c == 'S')
		win->texture_ptr = mlx_xpm_file_to_image(win->mlx_ptr, win->so_texture,
												&g_widht, &g_hight);
	if (c == 'W')
		win->texture_ptr = mlx_xpm_file_to_image(win->mlx_ptr, win->we_texture,
												&g_widht, &g_hight);
	if (c == 'E')
		win->texture_ptr = mlx_xpm_file_to_image(win->mlx_ptr, win->ea_texture,
												&g_widht, &g_hight);
	if (c == 's')
		win->texture_ptr = mlx_xpm_file_to_image(win->mlx_ptr, win->s_texture,
												&g_widht, &g_hight);
	if ((win->x_width != g_widht || win->y_hight != g_hight) && g_j)
		erreur_message("ERROR\ntexures should have the same dimentions", win);
	win->x_width = g_widht;
	win->y_hight = g_hight;
	if (!win->texture_ptr)
		erreur_message("ERROR\nthere is a problem open one xpm file", win);
	win->texture_data[i] = (int*)mlx_get_data_addr(win->texture_ptr, &win->bpp,
												&win->size_line, &win->endian);
	g_j++;
}

void		player_orientation(t_window *win)
{
	win->p.x = win->x_width * win->p.x + win->x_width / 2;
	win->p.y = win->y_hight * win->p.y + win->y_hight / 2;
	if (win->direction == 'S')
		win->angle = PI / 2;
	if (win->direction == 'N')
		win->angle = 3 * PI / 2;
	if (win->direction == 'E')
		win->direction = 0;
	if (win->direction == 'W')
		win->angle = PI;
}

void		initialization(t_window *win, int r)
{
	char	*texture;
	int		i;

	i = -1;
	texture = "NSWEs";
	if (!(win->mlx_ptr = mlx_init()))
		erreur_message("ERROR\n", win);
	if (!(win->win_ptr = mlx_new_window(win->mlx_ptr, win->width, win->hight,
															"CUB3D")))
		erreur_message("ERROR\n", win);
	if (!(win->img_ptr = mlx_new_image(win->mlx_ptr, win->width, win->hight)))
		erreur_message("ERROR\n", win);
	if (!(win->img_data = (int*)mlx_get_data_addr(win->img_ptr, &win->bpp,
										&win->size_line, &win->endian)))
		erreur_message("ERROR\n", win);
	while (texture[++i])
		get_texture(win, i, texture[i]);
	player_orientation(win);
	drawing_scene(win);
	if (r == 3)
		save(win);
}
