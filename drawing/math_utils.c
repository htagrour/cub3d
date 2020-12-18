/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 08:29:03 by htagrour          #+#    #+#             */
/*   Updated: 2020/02/29 14:03:44 by htagrour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int			rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

double		dmod(double x, double y)
{
	return (x - (int)(x / y) * y);
}

void		angle_adjust(double *angle)
{
	*angle = dmod(*angle, 2 * PI);
	*angle += (*angle < 0) ? 2 * PI : 0;
}

double		dist_between_points(double x1, double y1, double x2, double y2)
{
	return (sqrt((x1 - x2) * (x1 - x2) +
				(y1 - y2) * (y1 - y2)));
}

int			is_there_wall(t_window win, double x, double y)
{
	int max_x;
	int max_y;

	max_x = win.map_colums * win.x_width;
	max_y = win.map_raws * win.y_hight;
	if ((int)x >= max_x || (int)x <= 0 ||
			(int)y >= max_y || (int)y <= 0)
		return (1);
	return (win.map[(int)floor(y / win.y_hight)][(int)floor(x / win.x_width)]);
}
