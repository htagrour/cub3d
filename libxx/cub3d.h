#ifndef CUB3D_H
#define CUB3D_H
#include "/usr/local/include/mlx.h"
#include "get_next_line.h"
#include <math.h>
#include <fcntl.h>

void drawing_map(void *mlx_ptr, void *win_ptr);//, int witdh , int hieght);
typedef struct s_coord
{
    int x;
    int y;
}   t_coord;
#endif