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

/* int jl_moves(int x, int y, t_fract *f)
{
	if (fabs(f->c_r - x) > 5)
		f->c_r = x;
	if (fabs(f->c_i - y) > 5)
		f->c_i = y;
	return (0);
}
 */
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
	/*  	if (button >= 1 && button <= 3)
		f->jl_moves = (f->jl_moves == 1) ? 0 : 1;  */
	/* 	if (f->jl_moves == 1)
		jl_moves(x, y, f); */
	ft_mlx(f);
	return (1);
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
	f->init = 0;
	if (key == KEY_PLUS && f->type == 0)
		f->zoom += 50;
	else if (key == KEY_MINUS && f->type == 0)
		f->zoom -= 50;
	if (key == KEY_LEFT)
		f->xx -= 30 / f->zoom;
	else if (key == KEY_RIGHT)
		f->xx += 30 / f->zoom;
	else if (key == KEY_UP)
		f->yy -= 30 / f->zoom;
	else if (key == KEY_DOWN)
		f->yy += 30 / f->zoom;
	if (key == KEY_3)
		f->jl_moves = (f->jl_moves == 1) ? 0 : 1;
	else if (key == KEY_1)
		f->jl_moves = (f->jl_moves == 1) ? 0 : 1;
	else if (key == KEY_I)
	{
		psychodel(f);
	}
	else if (key == KEY_ESCAPE)
		finish(f);
	ft_mlx(f);
	return (0);
}
