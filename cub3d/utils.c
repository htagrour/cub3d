#include "cub3d.h"

void    extract_map(t_window *window)
{
    int fd;
    int i;
    int j;
    int k;
    char *line;

    j = 0;
    i = 1;
    fd = open("map.cub", O_RDONLY);
    window->map = (char**)malloc(sizeof(char*) * (MAP_NUM_ROWS + 1));
    while (i > 0)
    {
        window->map[j] = (char*)malloc(sizeof(char) * (MAP_NUM_COLS + 1));
        i = get_next_line(fd, &line);
        k = 0;
        while (*line)
        {
            if (*line != ' ')
                window->map[j][k++] = *line;
            line++;
        }
        window->map[j][k] = 0;
        j++;
    }
    window->map[j] = 0;
}

int is_there_wall(char **map, int x, int y)
{
    return (map[(y / (TAILE))][(x / (TAILE))] == '1');
}
int init_var(t_window *window)
{
    window->win_ptr = NULL;
    window->mlx_ptr = NULL;
    window->img_ptr = NULL;
    window->img_data = NULL;
    window->map = NULL;
    window->angle =0;
    window->x = 200;
    window->y = 100;
    return (1);
}

double dmod(double x, double y) {
    return x - (int)(x/y) * y;
}

void angle_adjust(double *angle)
{
    *angle = dmod(*angle, 2*PI);
    *angle += (*angle < 0) ? 2 * PI : 0;
}
double dist_calcul(t_coord p1, t_coord p2)
{
    return (sqrt((p1.x - p2.x) * (p1.x - p2.x)
                + (p1.y - p2.y) * (p1.y - p2.y)));
}
int     rgb_to_int(int r, int g, int b)
{
    return ((r << 16) | (g << 8) | b);
}