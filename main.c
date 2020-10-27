/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 08:19:00 by htagrour          #+#    #+#             */
/*   Updated: 2020/03/12 02:14:11 by htagrour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				ft_exit(t_window *win)
{
	if (win->map)
		free_window(win);
	exit(0);
}

void			file_validation(int *fd, char **v, int r, t_window *win)
{
	char	**str;
	int		index;

	if ((*fd = open(v[1], O_RDONLY)) < 0)
		erreur_message("ERROR\nfile not exist!!", win);
	if (r == 3)
		if (ft_strncmp("--save", v[2], ft_strlen(v[2])) != 0)
			erreur_message("ERROR\nunknow argument!!", win);
	index = sep_counter(v[1], '.');
	str = ft_split(v[1], '.');
	index -= (!str[index]) ? 1 : 0;
	if (ft_strncmp(str[index], "cub", 3) != 0)
		erreur_message("ERROR\nfile not .cub extention", win);
	free_all(str);
}

int				update_(t_window *win)
{
	mlx_hook(win->win_ptr, 2, 0, key_pressed, win);
	mlx_hook(win->win_ptr, 3, 0, key_relased, win);
	mlx_hook(win->win_ptr, 17, 0, ft_exit, win);
	update(win);
	return (1);
}

int				main(int r, char **v)
{
	t_window	win;
	int			fd;

	ft_bzero(&win, sizeof(win));
	if (r == 2 || r == 3)
	{
		file_validation(&fd, v, r, &win);
		read_file(&win, fd);
		initialization(&win, r);
		mlx_loop_hook(win.mlx_ptr, update_, &win);
		mlx_loop(win.mlx_ptr);
	}
	else
		erreur_message("ERROR\nfew or too many args", &win);
	return (0);
}
