/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 17:36:29 by htagrour          #+#    #+#             */
/*   Updated: 2020/03/12 00:00:33 by htagrour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "/usr/local/include/mlx.h"
# include "./get_next_line/get_next_line.h"
# include "./screenshot/screen_shot.h"
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>

# define ESC 53
# define LEFT 123
# define RIGHT 124
# define A 0
# define W 13
# define S 1
# define D 2
# define PI 3.141592654
# define FOV (PI / 3)
# define LINE_TAILL 1000
# define SPEED 15
# define SCALE 0.25
# define ROTATION_SPEED (PI / 60)
# define MAX_WIDTH 2048
# define MAX_HIGHT 1152
# define MIN_WIDTH 400
# define MIN_HIGHT 400

typedef struct		s_coord
{
	double			x;
	double			y;
}					t_coord;

typedef	struct		s_object
{
	t_coord			position;
	double			distance;
	int				is_ver;
	t_coord			center;
}					t_object;

typedef	struct		s_list
{
	t_object		obj;
	struct s_list	*next;
}					t_list;

typedef	struct		s_ray
{
	double			angle;
	double			dist;
	int				face_up;
	int				face_right;
	int				was_hit_vert;
	int				content;
	int				hit_objet;
	t_list			*obj;
	t_coord			insters;
}					t_ray;

typedef struct		s_window
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	int				*img_data;
	void			*texture_ptr;
	int				*texture_data[5];
	int				size_line;
	int				endian;
	int				bpp;
	int				**map;
	char			*no_texture;
	char			*so_texture;
	char			*we_texture;
	char			*ea_texture;
	char			*s_texture;
	int				no;
	int				so;
	int				we;
	int				ea;
	int				s;
	int				c;
	int				f;
	int				r;
	int				player;
	int				spec;
	int				m;
	char			direction;
	t_coord			p;
	int				x_width;
	int				y_hight;
	int				width;
	int				hight;
	int				f_color;
	int				c_color;
	int				walk_direction;
	int				rotate_direction;
	double			angle;
	double			inter_distance;
	int				map_colums;
	int				map_raws;
	t_coord			wall_inters;
}					t_window;

typedef	struct		s_vars
{
	t_coord			inter;
	double			xstep;
	double			ystep;
	int				content;
	double			wall_hitx;
	double			wall_hity;
	t_list			*obj;
	int				is_the_o;
	t_list			list;
}					t_vars;

typedef	struct		s_cvar
{
	double			projec_distance;
	int				wall_hieght;
	double			top_of_wall;
	double			buttom_of_wall;
	int				counter;
	int				offset_x;
	int				offset_y;
	double			distance;
}					t_cvar;

typedef	struct		s_ivar
{
	int				errr;
	int				e2;
	int				position;
}					t_ivar;

void				detection_process(t_window win, t_ray *ray);
void				drawline(t_coord end_coord, t_window *win, int color);
void				angle_adjust(double *angle);
int					is_there_wall(t_window win, double x, double y);
t_coord				inter_with_perp(t_window win, t_ray ray,
					t_coord center, double angle_center);
void				draw_walls_3d(t_window *window, t_ray *ray, int i);
t_coord				block_center(t_window win, t_object p);
int					rgb_to_int(int r, int g, int b);
void				draw_box(t_window *win, int index,
					t_coord coord, t_coord diment);
void				drawing_scene(t_window *window);
double				dist_between_points(double x1, double y1,
					double x2, double y2);
int					in_range(t_window win, double x, double y);
typedef	void		(*t_extract_fun)(char **str, t_window *win);
void				initialization(t_window *win, int r);
void				update(t_window *win);
int					key_relased(int key, t_window *window);
int					key_pressed(int key, t_window *window);
char				**ft_split(char const *str, char c);
int					ft_isdigit(int c);
int					ft_atoi(const char *str);
void				ft_lstadd_front(t_list **alst, t_list *new_);
t_list				*ft_lstnew(t_object obj);
void				ft_lstclear(t_list **lst);
int					ft_lstsize(t_list *list);
void				ft_bzero(void *s, size_t n);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_memcpy(void *des, const void *src, size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				lbubblesort(t_list *start);
void				add_to_list(t_list *list, t_ray *ray);
void				ft_resolution(char **str, t_window *win);
void				ft_texture(char **str, t_window *win);
void				ft_color(char **str, t_window *win);
void				ft_map(t_window *win, char *str, char **tem_map);
void				read_file(t_window *win, int fd);
int					texture_num(t_ray ray);
int					table_size(char **str, t_window *win);
int					dircetion(char c);
int					all_num(char *str);
int					player_index(char c);
void				erreur_message(char *str, t_window *win);
int					player_index(char c);
void				free_all(char **str);
void				save(t_window *win);
void				free_window(t_window *win);
int					ft_exit(t_window *win);
int					sep_counter(char *str, char c);
int					is_closed(char **map, int i, int j);
int					sep_counter(char *str, char c);
#endif
