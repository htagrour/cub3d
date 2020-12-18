/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 05:31:12 by htagrour          #+#    #+#             */
/*   Updated: 2019/11/12 17:00:25 by htagrour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t		ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*tab;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	tab = (char*)malloc(sizeof(char) *
		(ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!tab)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		tab[j++] = s1[i++];
	i = 0;
	while (s2[i])
		tab[j++] = s2[i++];
	tab[j] = '\0';
	return (tab);
}

char		*ft_strdup(const char *str)
{
	int		i;
	char	*a;

	i = 0;
	a = (char*)malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!a)
		return (0);
	while (str[i])
	{
		a[i] = str[i];
		i++;
	}
	a[i] = '\0';
	return (a);
}

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*tab;
	int		i;

	if (!s)
		return (NULL);
	tab = (char*)malloc(sizeof(char) * len + 1);
	if (!tab)
		return (NULL);
	i = 0;
	while (s[start] && len--)
		tab[i++] = s[start++];
	tab[i] = '\0';
	return (tab);
}
