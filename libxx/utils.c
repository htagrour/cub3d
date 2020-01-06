#include "cub3d.h"

void    extract_map(t_comp *com)
{
    int fd;
    int i;
    int j;
    int k;
    char *line;

    j = 0;
    i = 1;
    fd = open("fileDRawing.cub", O_RDONLY);
    com->map = malloc(sizeof(char*) * 23 + 1);
    while (i > 0)
    {
        com->map[j] = malloc(sizeof(char) * 48 + 1);
        i = get_next_line(fd, &line);
        k = 0;
        while (*line)
        {
            com->map[j][k] = *line;
            line++;
            k++;
        }
        com->map[j][k] = '\0';
        j++;
    }
    com->map[j] = NULL;
}

int is_there_wall(char **map, int x, int y)
{
    return (map[(y) / 20][(x) / 20] == '1');
}