#ifndef CUB3D_H
#define CUB3D_H
#include "/usr/local/include/mlx.h"
#include "get_next_line.h"
#include <math.h>
#include <fcntl.h>
#include <stdio.h>

/*windows properties*/
#define TAILE 32
#define MAP_NUM_ROWS 14
#define MAP_NUM_COLS 29

#define WIN_WIDTH (TAILE * MAP_NUM_COLS)
#define WIN_HIGHET (TAILE * MAP_NUM_ROWS)
#define ESC 53
#define LEFT 123
#define RIGHT 124
#define A 0
#define W 13
#define S 1
#define D 2
#define PI 3.141592654
#define FOV (PI / 3)
#define LINE_TAILL 1000
#define ARRAY_NUM (WIN_WIDTH / 1)
#define SPEED 10
#define SCALE 0.25
#define RADUIS (5 * SCALE)
#define ROTATION_SPEED (PI / 9)
typedef struct s_coord
{
    int x;
    int y;
} t_coord;

typedef struct  s_ray
{
    double angle;
    double dist;
    t_coord insters;
} t_ray;

typedef struct s_window
{
    void *mlx_ptr;
    void *win_ptr;
    void *img_ptr;
    int *img_data;
    int size_line;
    int endian;
    int bpp;
    char **map;
    int x;
    int y;
    int walk_direction;
    int rotate_direction;
    double angle;
    double inter_distance;
    t_coord wall_inters;
}       t_window;
void  extract_map(t_window *win_prep);
t_coord  drawline(t_coord end_coord, t_window *window, int color, int index);
void  plot_circle (t_window window, int x, int y, int color);
int  draw_box(t_window *window, int index , t_coord coord, t_coord diment, int color);
void drawing_map(t_window *window);
int init_var(t_window *window);
int is_there_wall(char **map, int x, int y);
int  update(t_window *window);
int  key_relased(int key, t_window *window);
int key_pressed(int key, t_window *window);
void angle_adjust(double *angle);
double dist_calcul(t_coord p1, t_coord p2);
#endif
