#include "fractol.h"

void zoom(int button, int x, int y, t_fract *f)
{
	if (button == 4)
	{
		f->xx = (x / f->zoom + f->xx) - (x / (f->zoom * 1.3));
		f->yy = (y / f->zoom + f->yy) - (y / (f->zoom * 1.3));
		f->zoom *= 1.3;
		f->iternum++;
	}
	else
	{
		f->xx = (x / f->zoom + f->xx) - (x / (f->zoom / 1.3));
		f->yy = (y / f->zoom + f->yy) - (y / (f->zoom / 1.3));
		f->zoom /= 1.3;
		f->iternum--;
	}
}

int ft_jl_moves(int x, int y, t_fract *f)
{
	if (f->jl_moves == 1)
	{
		if (fabs(f->c_r - x) > 5)
			f->c_r = x;
		if (fabs(f->c_i - y) > 5)
			f->c_i = y;
	};
	ft_mlx(f);
	return (0);
}

int ft_mouse(int button, int x, int y, t_fract *f)
{
	f->init = 0;
	if (button == 4 || button == 5)
		zoom(button, x, y, f);
	ft_mlx(f);
	return (1);
}

int ft_error(int c, t_fract *f)
{
	if (c == 1)
	{
		write(1, "usage: fractal name\n", 20);
		write(1, "\tmandelbrot/julia/duck/random\n", 30);
		exit(0);
	}
	free(f);
	return (0);
}

int finish(t_fract *f)
{
	if (f->img.img_ptr)
		mlx_destroy_image(f->mlx, f->img.img_ptr);
	mlx_destroy_window(f->mlx, f->win);
	free(f);
	exit(0);
	return (0);
}
