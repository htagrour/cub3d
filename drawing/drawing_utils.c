/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 08:42:53 by htagrour          #+#    #+#             */
/*   Updated: 2020/02/25 08:58:00 by htagrour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void		draw_box(t_window *win, int index, t_coord coord, t_coord diment)
{
	int		x;
	int		y;
	int		h;
	int		v;

	x = coord.x - 1;
	while (++x < (int)floor(coord.x + diment.x))
	{
		h = (int)floor(coord.y + diment.y);
		y = coord.y - 1;
		while (++y < h)
		{
			v = y * win->width + x;
			if (index)
				win->img_data[v] = 0x585858;
		}
	}
}

void		var_changement(t_ivar *v, t_coord *d, t_coord *w, t_coord *win)
{
	v->e2 = 2 * v->errr;
	if (v->e2 >= d->y)
	{
		v->errr += d->y;
		win->x += w->x;
	}
	if (v->e2 <= d->x)
	{
		v->errr += d->x;
		win->y += w->y;
	}
}

void		drawline(t_coord end_coord, t_window *win, int color)
{
	t_coord d_coord;
	t_coord w_coord;
	t_coord window;
	t_ivar	v;

	window.x = floor(win->p.x * SCALE);
	window.y = floor(win->p.y * SCALE);
	d_coord.x = fabs(end_coord.x - window.x);
	w_coord.x = (window.x < end_coord.x) ? 1 : -1;
	d_coord.y = -fabs(end_coord.y - window.y);
	w_coord.y = (window.y < end_coord.y) ? 1 : -1;
	v.errr = d_coord.x + d_coord.y;
	while (1)
	{
		v.position = (int)floor(window.y * win->width + window.x);
		win->img_data[v.position] = color;
		if ((window.x == end_coord.x && window.y == end_coord.y))
			break ;
		var_changement(&v, &d_coord, &w_coord, &window);
	}
}
