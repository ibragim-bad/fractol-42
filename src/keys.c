#include "../include/fractol.h"

int     ft_key(int key, t_fract *f)
{

    if (key == KEY_PLUS)
       f->zoom += 50;
    else if (key == KEY_MINUS)
        f->zoom -= 50;
    if (key == KEY_LEFT)
		f->xx -= 30 / f->zoom;
	else if (key == KEY_RIGHT)
		f->xx += 30 / f->zoom;
	else if (key == KEY_UP)
		f->yy -= 30 / f->zoom;
	else if (key == KEY_DOWN)
		f->yy += 30 / f->zoom;
	else if (key == KEY_PLUS)
		f->iternum++;
	else if (key == KEY_MINUS)
		f->iternum--;
	else if (key == KEY_ESCAPE)
		exit(0);
    ft_mlx(f);
    return (0);
}