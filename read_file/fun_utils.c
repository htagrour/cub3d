/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 10:30:05 by htagrour          #+#    #+#             */
/*   Updated: 2020/03/12 01:43:11 by htagrour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		is_closed(char **map, int i, int j)
{
	int		befor;
	int		after;

	befor = ft_strlen(map[j - 1]) - 1;
	after = ft_strlen(map[j + 1]) - 1;
	if (i > befor || i > after || map[j][i - 1] == ' ' ||
		map[j][i + 1] == ' ' || map[j - 1][i] == ' ' || map[j + 1][i] == ' ')
		return (0);
	return (1);
}

int		player_index(char c)
{
	return (c == 'N' ||
			c == 'S' ||
			c == 'E' ||
			c == 'W');
}

int		dircetion(char c)
{
	return (c == 'O' || c == 'E' ||
			c == 'A' || !c);
}

int		all_num(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

void	erreur_message(char *str, t_window *win)
{
	ft_putstr_fd(str, 1);
	ft_exit(win);
}
