/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 04:21:16 by htagrour          #+#    #+#             */
/*   Updated: 2020/03/11 07:48:03 by htagrour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int			in_range(t_window win, double x, double y)
{
	int max_x;
	int max_y;

	max_x = win.map_colums * win.x_width;
	max_y = win.map_raws * win.y_hight;
	return (x >= 0 && x <= max_x &&
			y >= 0 && y <= max_y);
}

t_coord		inter_with_perp(t_window win, t_ray ray, t_coord center,
			double angle_center)
{
	t_coord	p;
	double	angle_ph;

	angle_ph = angle_center - ray.angle;
	if (center.x < win.p.x)
		angle_ph += PI;
	angle_adjust(&angle_ph);
	p.x = win.p.x + (center.x - win.p.x) * cos(angle_ph) -
					(center.y - win.p.y) * sin(angle_ph);
	p.y = win.p.y + (center.x - win.p.x) * sin(angle_ph) +
					(center.y - win.p.y) * cos(angle_ph);
	return (p);
}

t_coord		block_center(t_window win, t_object p)
{
	t_coord	center;
	int		xblock;
	int		yblock;

	xblock = (int)floor(p.position.x / win.x_width);
	center.x = xblock * win.x_width + win.x_width / 2;
	yblock = (int)floor(p.position.y / win.y_hight);
	center.y = yblock * win.y_hight + win.y_hight / 2;
	return (center);
}

int			texture_num(t_ray ray)
{
	if (ray.face_up && !ray.was_hit_vert)
		return (0);
	if (!ray.face_up && !ray.was_hit_vert)
		return (1);
	if (ray.face_right && ray.was_hit_vert)
		return (3);
	if (!ray.face_right && ray.was_hit_vert)
		return (2);
	return (0);
}
