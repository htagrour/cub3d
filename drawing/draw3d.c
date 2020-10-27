/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 03:08:04 by htagrour          #+#    #+#             */
/*   Updated: 2020/03/11 07:51:51 by htagrour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void		var_adjust(t_cvar *var, t_window win, t_ray ray, int index)
{
	var->distance *= cos(ray.angle - win.angle);
	if (!var->distance)
		var->distance++;
	var->projec_distance = (double)(win.width / 2) / tan(FOV / 2);
	var->wall_hieght = (win.y_hight / var->distance) * var->projec_distance;
	var->top_of_wall = (win.hight / 2) - (var->wall_hieght / 2);
	var->top_of_wall *= (var->top_of_wall < 0) ? 0 : 1;
	var->buttom_of_wall = (win.hight / 2) + (var->wall_hieght / 2);
	var->buttom_of_wall = (var->buttom_of_wall > win.hight) ?
		win.hight : var->buttom_of_wall;
	if (index)
		var->offset_x = (ray.was_hit_vert) ? (int)ray.insters.y % win.y_hight :
			(int)ray.insters.x % win.x_width;
}

void		paint_texture(t_window *win, t_cvar var, int i, int txt)
{
	int		counter;
	int		dist_from_top;
	int		color;

	counter = var.top_of_wall - 1;
	while (++counter < var.buttom_of_wall)
	{
		dist_from_top = counter + (var.wall_hieght / 2) - (win->hight / 2);
		var.offset_y = (int)floor(dist_from_top *
						((float)win->y_hight / var.wall_hieght));
		color = win->texture_data[txt][win->x_width * var.offset_y +
														var.offset_x];
		if (color)
			win->img_data[counter * win->width + i] = color;
	}
}

void		paint_sprite(t_window *win, t_ray ray, t_object obj, int i)
{
	t_coord	p;
	t_cvar	var;
	t_coord	center;
	double	angle_center;
	t_coord x;

	center = block_center(*win, obj);
	angle_center = atan((center.y - win->p.y) / (center.x - win->p.x));
	angle_adjust(&angle_center);
	p = inter_with_perp(*win, ray, center, angle_center);
	var.distance = dist_between_points(win->p.x, win->p.y, center.x, center.y);
	var_adjust(&var, *win, ray, 0);
	x.x = center.x + cos(angle_center - PI / 2) * win->x_width / 2;
	x.y = center.y + sin(angle_center - PI / 2) * win->x_width / 2;
	var.distance = dist_between_points(x.x, x.y, p.x, p.y);
	var.offset_x = var.distance;
	var.distance = dist_between_points(center.x, center.y, p.x, p.y);
	if (var.offset_x > 0 && ray.dist > obj.distance &&
						var.distance <= win->x_width / 2)
		paint_texture(win, var, i, 4);
}

void		paint_wall(t_window *win, t_ray ray, int i)
{
	t_cvar	var;
	int		counter;
	int		texture;

	var.distance = ray.dist;
	var_adjust(&var, *win, ray, 1);
	counter = -1;
	while (++counter < var.top_of_wall)
		win->img_data[counter * win->width + i] = win->c_color;
	counter = var.buttom_of_wall - 1;
	while (++counter < win->hight)
		win->img_data[counter * win->width + i] = win->f_color;
	texture = texture_num(ray);
	paint_texture(win, var, i, texture);
}

void		draw_walls_3d(t_window *win, t_ray *ray, int i)
{
	t_list	*ptr;

	paint_wall(win, *ray, i);
	if (ray->hit_objet)
	{
		ptr = ray->obj;
		lbubblesort(ptr);
		while (ptr)
		{
			paint_sprite(win, *ray, ptr->obj, i);
			ptr = ptr->next;
		}
		ft_lstclear(&ray->obj);
	}
}
