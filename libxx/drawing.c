#include "cub3d.h"

int draw_box(void *mlx_ptr, void *win_ptr, int index , t_coord coord)
{
    int x;
    int y;

    x = coord.x -1;
    while ( (++x < coord.x + 20))
    {
        y = coord.y - 1;
        while (++y < coord.y + 20)
        {   if (index == '1')  
            mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0xB22222);
        }

    }
    return (1);
}

void drawing_map(void *mlx_ptr, void *win_ptr)//, int witdh , int hieght)
{
    int fd;
    fd = open("fileDRawing.txt", O_RDONLY);
    int i = 1;
    char *line;
    t_coord coord;

    coord.x = 20;
    coord.y = 20;

    while (i > 0)
    {
        i = get_next_line(fd, &line);
        while (*line)
        {
            draw_box(mlx_ptr, win_ptr, *line, coord);
            coord.x += 20;
            line++;
        }
        coord.x = 20;
        coord.y += 20;
       // free(line);
    }
}