/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 08:02:57 by htagrour          #+#    #+#             */
/*   Updated: 2020/02/25 09:04:54 by htagrour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void			ft_lstadd_front(t_list **alst, t_list *new)
{
	if (*alst)
	{
		new->next = *alst;
		*alst = new;
	}
	else
		*alst = new;
}

t_list			*ft_lstnew(t_object obj)
{
	t_list		*tab;

	tab = malloc(sizeof(t_list));
	if (!tab)
		return (NULL);
	tab->obj = obj;
	tab->next = NULL;
	return (tab);
}

void			ft_lstclear(t_list **lst)
{
	t_list		*ptr;
	t_list		*ptr1;

	ptr = *lst;
	if (ptr)
	{
		while (ptr)
		{
			ptr1 = ptr->next;
			free(ptr);
			ptr = ptr1;
		}
		*lst = NULL;
	}
}

void			lswap(t_list *a, t_list *b)
{
	t_object	temp;

	temp = a->obj;
	a->obj = b->obj;
	b->obj = temp;
}

void			lbubblesort(t_list *start)
{
	int			swapped;
	t_list		*ptr1;
	t_list		*lptr;

	lptr = NULL;
	if (start == NULL)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		ptr1 = start;
		while (ptr1->next != lptr)
		{
			if (ptr1->obj.distance < ptr1->next->obj.distance)
			{
				lswap(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
}
