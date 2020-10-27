/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_shot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 16:13:44 by htagrour          #+#    #+#             */
/*   Updated: 2020/03/01 09:10:55 by htagrour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int					fillhdr(t_filehdr *filehdr, t_infohdr *infohdr,
					t_window win)
{
	int				bitcount;
	int				width_in_bytes;
	uint32_t		imagesize;

	bitcount = 24;
	width_in_bytes = ((win.width * bitcount + 31) / 32) * 4;
	imagesize = width_in_bytes * win.hight;
	filehdr->bf_size = 54 + imagesize;
	filehdr->bf_off_bits = 54;
	infohdr->bi_size = 40;
	infohdr->bi_planes = 1;
	infohdr->bi_width = win.width;
	infohdr->bi_height = win.hight;
	infohdr->bi_bit_count = bitcount;
	infohdr->bi_size_image = imagesize;
	return (width_in_bytes);
}

void				free_window(t_window *win)
{
	int				j;

	j = -1;
	while (++j < win->map_raws)
		free(win->map[j]);
	free(win->map);
}

void				fill_buf(unsigned char **buf, t_infohdr infohdr,
					t_window win, int width_in_bit)
{
	int				y;
	int				row;
	unsigned int	x;
	int				col;

	y = 0;
	row = infohdr.bi_height - 1;
	while (row >= 0)
	{
		col = -1;
		while (++col < infohdr.bi_width)
		{
			x = win.img_data[y * win.width + col];
			(*buf)[row * width_in_bit + col * 3 + 0] = (x & 0x000000ff);
			(*buf)[row * width_in_bit + col * 3 + 1] = (x & 0x0000ff00) >> 8;
			(*buf)[row * width_in_bit + col * 3 + 2] = (x & 0x00ff0000) >> 16;
		}
		y++;
		row--;
	}
}

void				save(t_window *win)
{
	t_filehdr		filehdr;
	t_infohdr		infohdr;
	int				width_in_bit;
	unsigned char	*buf;
	int				fd;

	ft_bzero(&filehdr, sizeof(filehdr));
	ft_bzero(&infohdr, sizeof(infohdr));
	ft_memcpy(&filehdr, "BM", 2);
	width_in_bit = fillhdr(&filehdr, &infohdr, *win);
	if (!(buf = malloc(infohdr.bi_size_image)))
		erreur_message("ERROR\nan allocation failed!!", win);
	fd = open("test.bmp", O_CREAT | O_WRONLY, 777);
	fill_buf(&buf, infohdr, *win, width_in_bit);
	write(fd, &filehdr, sizeof(filehdr));
	write(fd, &infohdr, sizeof(infohdr));
	write(fd, (char*)buf, infohdr.bi_size_image);
	close(fd);
	free(buf);
	ft_exit(win);
}
