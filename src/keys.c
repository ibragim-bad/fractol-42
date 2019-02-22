#include "fractol.h"

int finish(t_fract *f)
{
	mlx_destroy_image(f->mlx, f->img.img_ptr);
	mlx_destroy_window(f->mlx, f->win);
	exit(0);
	return (0);
}

int psychodel(t_fract *f)
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
	mlx_destroy_image(f->mlx, f->img.img_ptr);
	f->init = 0;
	if (key == KEY_PLUS && f->type == 0)
		f->zoom += 50;
	else if (key == KEY_MINUS && f->type == 0)
		f->zoom -= 50;
	if (key == KEY_PLUS && f->type == 1)
	{
		f->zoom += 0.1;
		if (f->zoom > 0.5)
			f->level = 10;
		else if (f->zoom < 0.5)
			f->level = 8;
	}
	else if (key == KEY_MINUS && f->type == 1)
	{
		f->zoom -= 0.1;
		if (f->zoom > 0.5)
			f->level = 10;
		else if (f->zoom < 0.5)
			f->level = 8;
	}
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
	else if (key == KEY_I)
	{
		psychodel(f);
	}
	else if (key == KEY_ESCAPE)
		exit(0);
	ft_mlx(f);
	return (0);
}