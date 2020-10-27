/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 16:48:11 by htagrour          #+#    #+#             */
/*   Updated: 2020/03/12 00:10:32 by htagrour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int			g_index;
char		*g_line;
char		**g_str;
char		**g_tem_map;

static const	t_extract_fun g_function[255] =
{
	['R'] = ft_resolution,
	['N'] = ft_texture,
	['S'] = ft_texture,
	['W'] = ft_texture,
	['E'] = ft_texture,
	['F'] = ft_color,
	['C'] = ft_color
};

char			skip_spaces(char *str, int inc, int start)
{
	while (start >= 0 && str[start])
	{
		if (str[start] != ' ')
			return (str[start]);
		str += inc;
	}
	return (0);
}

void			map_adjust(t_window *win, char **tem_map)
{
	int		i;
	int		j;
	char	c;

	i = -1;
	win->map = malloc(sizeof(int*) * win->map_raws);
	while (tem_map[++i])
	{
		j = -1;
		win->map[i] = malloc(sizeof(int) * win->map_colums);
		while ((c = tem_map[i][++j]))
			win->map[i][j] = (c != ' ') ? c - '0' : 0;
		while (j < win->map_colums)
			win->map[i][++j] = 0;
	}
	free_all(tem_map);
}

void			check_map_errors(t_window *win, char **tem_map)
{
	int			j;
	int			i;
	char		c;

	j = -1;
	if (win->spec)
		erreur_message("ERROR\nmap is separted by empty line", win);
	if (!win->player)
		erreur_message("ERROR\nplayer index not exist", win);
	while (tem_map[++j])
	{
		i = -1;
		if (skip_spaces(tem_map[j], 1, 0) != '1' ||
			skip_spaces(tem_map[j], -1, ft_strlen(tem_map[j]) - 1) != '1')
			erreur_message("ERROR\nmap not closed by walls", win);
		while ((c = tem_map[j][++i]))
		{
			if ((c == '0' && (!j || j == win->map_raws - 1)) ||
				(c == '0' && !is_closed(tem_map, i, j)))
				erreur_message("ERROR\nmap not closed by walls", win);
			if (!player_index(c) && c != '1' && c != ' ' &&
									c != '0' && c != '2')
				erreur_message("ERROR\ninvalide caracter in map", win);
		}
	}
}

void			read_file(t_window *win, int fd)
{
	g_tem_map = (char **)malloc(sizeof(char*) * (1024));
	g_index = 1;
	while (g_index > 0)
	{
		g_index = get_next_line(fd, &g_line);
		if (!g_line[0])
		{
			win->spec = (win->map_raws) ? 1 : 0;
			free_(&g_line);
			continue ;
		}
		g_str = ft_split(g_line, ' ');
		if (!g_function[(int)*g_str[0]] && *g_str[0] != '1')
			erreur_message("your cub file not valide\n", win);
		if (*g_str[0] == '1')
			ft_map(win, g_line, g_tem_map);
		else
			g_function[(int)*g_str[0]](g_str, win);
		free_(&g_line);
		free_all(g_str);
	}
	g_tem_map[win->map_raws] = NULL;
	check_map_errors(win, g_tem_map);
	map_adjust(win, g_tem_map);
}
