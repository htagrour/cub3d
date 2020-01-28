/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 21:52:32 by htagrour          #+#    #+#             */
/*   Updated: 2019/11/12 17:00:23 by htagrour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			isthereaback(char *str)
{
	int		index;

	index = 0;
	while (str[index])
	{
		if (str[index] == '\n')
			return (1);
		index++;
	}
	return (0);
}

int			free_(char **str)
{
	free(*str);
	*str = NULL;
	return (0);
}

int			add_line(char **str, int fd)
{
	char	*tem;
	int		i;
	char	*ptr;

	i = 1;
	while (i > 0)
	{
		if (!(tem = (char*)malloc(sizeof(char) * BUFFER_SIZE + 1)) ||
		(i = read(fd, tem, BUFFER_SIZE)) == -1)
			return (-1);
		tem[i] = '\0';
		ptr = *str;
		if (!(*str = ft_strjoin(*str, tem)))
			return (-1);
		free_(&ptr);
		free_(&tem);
		if (isthereaback(*str))
			break ;
	}
	return (i);
}

int			get_next_line(int fd, char **line)
{
	static char		*rest;
	int				counter;
	int				read_value;
	char			*ptr;

	counter = 0;
	if (!line || read(fd, NULL, 0) != 0 || BUFFER_SIZE < 0)
		return (-1);
	if (!rest)
		if (!(rest = ft_strdup("")))
			return (-1);
	if ((read_value = add_line(&rest, fd)) == -1)
		return (-1);
	while (rest[counter] != '\n' && rest[counter])
		counter++;
	if (!(*line = ft_substr(rest, 0, counter)))
		return (-1);
	if (rest[counter] != '\n' && !read_value)
		return (free_(&rest));
	ptr = rest;
	if (!(rest = ft_strdup(rest + counter + 1)))
		return (-1);
	free_(&ptr);
	return (1);
}
