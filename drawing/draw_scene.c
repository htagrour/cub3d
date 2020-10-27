/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 04:11:11 by htagrour          #+#    #+#             */
/*   Updated: 2020/03/12 01:39:30 by htagrour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void		draw_walls_2d(t_window *win)
{
	t_coord	coord;
	t_coord	dimen;
	int		j;
	int		k;

	dimen.x = win->x_width * SCALE;
	dimen.y = win->y_hight * SCALE;
	coord.x = 0;
	coord.y = 0;
	j = 0;
	while (j < win->map_raws)
	{
		k = 0;
		while (k < win->map_colums)
		{
			draw_box(win, win->map[j][k++], coord, dimen);
			coord.x += dimen.x;
		}
		coord.x = 0;
		coord.y += dimen.y;
		j++;
	}
}

void		add_to_list(t_list *list, t_ray *ray)
{
	t_list	*ptr;

	ptr = list;
	while (ptr)
	{
		ft_lstadd_front(&ray->obj, ft_lstnew(ptr->obj));
		ptr = ptr->next;
	}
}

void		calculation_process(t_window *win, t_ray *ray)
{
	ray->face_up = (ray->angle > 0 && ray->angle < PI) ? 0 : 1;
	ray->face_right = (ray->angle < PI * 0.5 || ray->angle > PI * 1.5) ? 1 : 0;
	angle_adjust(&ray->angle);
	detection_process(*win, ray);
}

void		draw_fov(t_window *window, t_ray ray)
{
	ray.insters.x = floor(ray.insters.x * SCALE);
	ray.insters.y = floor(ray.insters.y * SCALE);
	drawline(ray.insters, window, 0x004d00);
}

void		drawing_scene(t_window *win)
{
	t_ray	ray[win->width];
	int		i;

	i = 0;
	ft_bzero(&ray[i], sizeof(t_ray));
	ray[i].angle = win->angle - FOV / 2;
	while (i < win->width)
	{
		ray[i].obj = NULL;
		calculation_process(win, &ray[i]);
		draw_walls_3d(win, &ray[i], i);
		ray[i + 1].angle = ray[i].angle + FOV / win->width;
		i++;
	}
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
}
