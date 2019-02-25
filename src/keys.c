#include "fractol.h"

static int key_moves(int key, t_fract *f)
{
	if (key == KEY_LEFT)
		f->xx -= 30 / f->zoom;
	else if (key == KEY_RIGHT)
		f->xx += 30 / f->zoom;
	else if (key == KEY_UP)
		f->yy -= 30 / f->zoom;
	else if (key == KEY_DOWN)
		f->yy += 30 / f->zoom;
	return (0);
}

static int psychodel(t_fract *f)
{
	if (f->color != 0xFFFFFF)
		f->color += 3000;
	else
		f->color = 0x00F000;
	ft_mlx(f);
	return (0);
}

int ft_key(int key, t_fract *f)
{
	f->init = 0;
	key_moves(key, f);
	if (key == KEY_PLUS)
		f->zoom += 50;
	else if (key == KEY_MINUS)
		f->zoom -= 50;
	else if (key == KEY_1)
		f->jl_moves = (f->jl_moves == 1) ? 0 : 1;
	else if (key == KEY_2)
		f->iternum++;
	else if (key == KEY_3)
		f->iternum--;
	else if (key == KEY_5)
		f->init = 1;
	else if (key == KEY_0)
		psychodel(f);
	else if (key == KEY_ESCAPE)
		finish(f);
	ft_mlx(f);
	return (0);
}
