#include "cub3d.h"

int main()
{
    void *mlx_ptr;
    void *win_ptr;
    //int x;
    //int y1;
    //int y2;
    //int radius;
    int win_width;
    int win_hieght;

    win_hieght = 500;
    win_width = 1000;
    //x = -1;
    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window( mlx_ptr, win_width, win_hieght, "hello wolrd");
    drawing_map(mlx_ptr, win_ptr);//, win_width, win_hieght);  
    mlx_loop(mlx_ptr);
    return (0);
}

/* print all screen
while ( ++x < win_width)
    {
        y1 = -1;
        while ( ++y1 < win_hieght)
        {
            if (pow(x - win_width /2, 2) + pow(y1 - win_hieght / 2, 2) == pow(radius, 2))
                mlx_pixel_put(mlx_ptr, win_ptr, x, y1, 0xB22222);
        }

    }
*/

/* print rectange
while ( ++x < win_width - win_width / 4)
    {
        y1 = win_width / 4 - 1 ;
        while ( ++y1 < win_width - win_width / 4)
        {
            if (!(in_rang(y1, win_width / 3, win_width - win_width / 3) && in_rang(x, win_width / 3, win_width - win_width / 3)))
                mlx_pixel_put(mlx_ptr, win_ptr, x, y1, 0xB22222);
        }

    }
*/
