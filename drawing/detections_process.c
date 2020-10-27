/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detections_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 02:42:19 by htagrour          #+#    #+#             */
/*   Updated: 2020/02/29 14:07:08 by htagrour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void			coord(t_window win, t_vars *var)
{
	t_object	obj;
	int			content;

	var->is_the_o = 0;
	while (in_range(win, var->inter.x, var->inter.y))
	{
		if ((content = is_there_wall(win, var->inter.x, var->inter.y)) == 1)
		{
			var->content = content;
			break ;
		}
		if ((content = is_there_wall(win, var->inter.x, var->inter.y)) == 2)
		{
			obj.position = var->inter;
			obj.distance = dist_between_points(win.p.x, win.p.y,
					var->inter.x, var->inter.y);
			ft_lstadd_front(&var->obj, ft_lstnew(obj));
			var->is_the_o = 1;
		}
		var->inter.x += var->xstep;
		var->inter.y += var->ystep;
	}
}

void			vert_inter(t_window win, t_ray ray, t_vars *var)
{
	ft_bzero(var, sizeof(t_vars));
	var->inter.x = floor(win.p.x / win.x_width) * win.x_width;
	var->inter.x += (ray.face_right) ? win.x_width : 0;
	var->inter.y = win.p.y + (var->inter.x - win.p.x) * tan(ray.angle);
	var->xstep = win.x_width;
	var->xstep *= (!ray.face_right) ? -1 : 1;
	var->ystep = var->xstep * tan(ray.angle);
	var->ystep *= ((ray.face_up && var->ystep > 0) ||
			(!ray.face_up && var->ystep < 0)) ? -1 : 1;
	if (!ray.face_right)
		var->inter.x--;
	coord(win, var);
}

void			horz_inter(t_window win, t_ray ray, t_vars *var)
{
	ft_bzero(var, sizeof(t_vars));
	var->inter.y = floor(win.p.y / win.y_hight) * win.y_hight;
	var->inter.y += (!ray.face_up) ? win.y_hight : 0;
	var->inter.x = win.p.x + (var->inter.y - win.p.y) / tan(ray.angle);
	var->ystep = win.y_hight;
	var->ystep *= (ray.face_up) ? -1 : 1;
	var->xstep = var->ystep / tan(ray.angle);
	var->xstep *= (!ray.face_right && var->xstep > 0) ? -1 : 1;
	var->xstep *= (ray.face_right && var->xstep < 0) ? -1 : 1;
	if (ray.face_up)
		var->inter.y--;
	coord(win, var);
}

void			closest_inster(t_window win, t_vars v, t_vars h, t_ray *ray)
{
	double		v_distance;
	double		h_distance;

	v_distance = (v.content) ?
		dist_between_points(v.inter.x, v.inter.y, win.p.x, win.p.y) : 200000;
	h_distance = (h.content) ?
		dist_between_points(h.inter.x, h.inter.y, win.p.x, win.p.y) : 200000;
	ray->dist = (v_distance > h_distance) ? h_distance : v_distance;
	ray->insters = (v_distance > h_distance) ? h.inter : v.inter;
	ray->was_hit_vert = (v_distance > h_distance) ? 0 : 1;
	ray->content = (v_distance > h_distance) ? h.content : v.content;
	ray->hit_objet = (h.is_the_o || v.is_the_o) ? 1 : 0;
}

void			detection_process(t_window win, t_ray *ray)
{
	t_vars		vert;
	t_vars		horz;

	vert_inter(win, *ray, &vert);
	horz_inter(win, *ray, &horz);
	if (!ray->face_right)
		vert.inter.x++;
	if (ray->face_up)
		horz.inter.y++;
	closest_inster(win, vert, horz, ray);
	add_to_list(vert.obj, ray);
	ft_lstclear(&vert.obj);
	add_to_list(horz.obj, ray);
	ft_lstclear(&horz.obj);
}
