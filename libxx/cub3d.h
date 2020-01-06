#ifndef CUB3D_H
#define CUB3D_H
#include "/usr/local/include/mlx.h"
#include "get_next_line.h"
#include <math.h>
#include <fcntl.h>
#include <stdio.h>

#define PI 3.141592654
typedef struct s_comp
{
    int player_x;
    int player_y;
    double angle;
    int rotate_direction;
    int walk_direction;
    void *mlx_ptr;
    char **map;
    void *win_ptr;
    int speed;
}   t_comp;

typedef struct s_coord
{
    int x;
    int y;
}   t_coord;
int update(int key, t_comp *com);
int update_x(int key, int x, int y, t_comp *com);
void drawing_map(t_comp *comp);//, int witdh , int hieght);
void    extract_map(t_comp *com);
int is_there_wall(char **map, int x, int y);
#endif
