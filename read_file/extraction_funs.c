/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extraction_funs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 10:37:18 by htagrour          #+#    #+#             */
/*   Updated: 2020/03/12 02:01:49 by htagrour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int			g_j;
int			g_total;
int			g_player;

void		ft_resolution(char **str, t_window *win)
{
	if (str[0][1] || str[3])
		erreur_message("ERROR\nthere is a preblem in resolution section", win);
	if (!all_num(str[1]) || !all_num(str[2]))
		erreur_message("ERROR\nthere is a problem in one of width or hight",
						win);
	if ((win->width = ft_atoi(str[1])) <= 0)
		erreur_message("ERROR\nthe width is samll or equal to zero", win);
	if ((win->hight = ft_atoi(str[2])) <= 0)
		erreur_message("ERROR\nthe hight is samll or equal to zero", win);
	win->width = (win->width > MAX_WIDTH) ? MAX_WIDTH : win->width;
	win->hight = (win->hight > MAX_HIGHT) ? MAX_HIGHT : win->hight;
	win->width = (win->width < MIN_WIDTH) ? MIN_WIDTH : win->width;
	win->hight = (win->hight < MIN_HIGHT) ? MIN_HIGHT : win->hight;
	if (++win->r > 1)
		erreur_message("ERROR\nresolution is doubled!!", win);
	g_total++;
}

void		check_double(char *str, t_window *win)
{
	if (str[1] == 'O')
	{
		if (str[0] == 'N')
			win->no++;
		else
			win->so++;
	}
	if (str[1] == 'E')
		win->we++;
	if (str[1] == 'A')
		win->ea++;
	if (!str[1])
		win->s++;
	if (win->no > 1 || win->so > 1 || win->we > 1 ||
						win->ea > 1 || win->s > 1)
		erreur_message("ERROR\none of texture is doubled!!", win);
}

void		ft_texture(char **str, t_window *win)
{
	int		fd;

	if (win->map_raws)
		erreur_message("ERROR\nplayer out of maze or map pos error", win);
	if (!dircetion(str[0][1]) || str[2] || str[0][2])
		erreur_message("ERROR\nproblem in one of your textures", win);
	if (str[0][1] == 'O')
	{
		if (str[0][0] == 'N')
			win->no_texture = ft_strdup(str[1]);
		else
			win->so_texture = ft_strdup(str[1]);
	}
	if (str[0][1] == 'E')
		win->we_texture = ft_strdup(str[1]);
	if (str[0][1] == 'A')
		win->ea_texture = ft_strdup(str[1]);
	if (!str[0][1])
		win->s_texture = ft_strdup(str[1]);
	if ((fd = open(str[1], O_RDONLY)) < 0)
		erreur_message("ERROR\nproblem opening one of your xpm file", win);
	close(fd);
	check_double(str[0], win);
	g_total++;
}

void		ft_color(char **str, t_window *win)
{
	int		r;
	int		g;
	int		b;
	char	**color;

	if (win->m)
		erreur_message("ERROR\nmap not valide", win);
	color = ft_split(str[1], ',');
	if (str[0][1] || str[2] || sep_counter(str[1], ',') != 2 || !color[2])
		erreur_message("ERROR\nproblem in one of your colors", win);
	if (!all_num(color[0]) || !all_num(color[1]) || !all_num(color[2]))
		erreur_message("ERROR\nwtf!!! this is not a color value", win);
	if ((r = ft_atoi(color[0])) < 0 || r > 255)
		erreur_message("ERROR\none of color value is out of range", win);
	if ((g = ft_atoi(color[1])) < 0 || g > 255)
		erreur_message("ERROR\none of color value is out of range", win);
	if ((b = ft_atoi(color[2])) < 0 || b > 255)
		erreur_message("ERROR\none of color value is out of range", win);
	if (*str[0] == 'C' && ++win->c && ++g_total)
		win->c_color = rgb_to_int(r, g, b);
	if (*str[0] == 'F' && ++win->f && ++g_total)
		win->f_color = rgb_to_int(r, g, b);
	free_all(color);
	if (win->f > 1 || win->c > 1)
		erreur_message("ERRPR\none color is doubled!!", win);
}

void		ft_map(t_window *win, char *str, char **tem_map)
{
	int		i;
	char	c;
	int		lenght;

	i = -1;
	lenght = ft_strlen(str);
	if (g_total != 8)
		erreur_message("ERROR\nelement is missing or map position error", win);
	tem_map[win->map_raws] = malloc(sizeof(char) * (lenght + 1));
	while ((c = str[++i]))
	{
		if (player_index(c))
		{
			if (win->player++)
				erreur_message("ERROR\ndouble player index", win);
			win->p.x = i;
			win->p.y = win->map_raws;
			win->direction = c;
			c = '0';
		}
		tem_map[win->map_raws][i] = c;
	}
	tem_map[win->map_raws][i] = 0;
	win->map_colums = (win->map_colums < lenght) ? lenght : win->map_colums;
	win->map_raws++;
}
