#include "../include/fractol.h"

int		ft_putter(t_fract *f)
{
	f->c_r = 1.0 * f->x / f->zoom + f->xx;
	f->c_i = 1.0 * f->y / f->zoom + f->yy;
	f->a_r = 0;
	f->a_i = 0;
	f->i = 0;
	while (f->i < f->iternum && (f->a_r * f->a_r + f->a_i * f->a_i) < 4)
	{
		f->b_r = 1.0 * (f->a_r * f->a_r - f->a_i * f->a_i);
		f->b_i = 2.0 * f->a_r * f->a_i;
		f->a_r = 1.0 * (f->b_r + f->c_r);
		f->a_i = 1.0 * (f->b_i + f->c_i);
		f->i++;
	}
	if (f->i == f->iternum)
		f->img.data[f->y * WINSIZE + f->x] = 0x000000;
	else
		f->img.data[f->y * WINSIZE + f->x] = f->color * f->i;
	return (0);
}

void	*mandelbrot(void *fr)
{
	t_fract	*f;

	f = fr;
	while (f->y < f->y_max)
	{
		f->x = 0;
		while (f->x < WINSIZE)
		{
			ft_putter(f);
			f->x++;
		}
		f->y++;
	}
	return (f);
}

int		ft_init_mndb(t_fract *f)
{
	f->y = 0;
	f->x = 0;
	if (f->zoom)
        return (0);
    f->zoom = WINSIZE / 3;
	f->xx = -2.05;
	f->yy = -1.3;
	f->color = 0xC8FFFD;
	f->inverter = 1;
	f->black = 1;
	f->iternum = ITERNUM;
	f->y_max = WINSIZE;
	f->inverter = 1;
	f->black = 1;
	return (0);
}

int		ft_mndb(t_fract *f)
{
	if (!(f->img.img_ptr = mlx_new_image(f->mlx, WINSIZE, WINSIZE)))
		return (-1);
	f->img.data = (int *)mlx_get_data_addr(f->img.img_ptr, &f->img.bpp,
			&f->img.size_l, &f->img.endian);
	ft_init_mndb(f);
	mandelbrot(f);
	mlx_put_image_to_window(f->mlx, f->win, f->img.img_ptr, 0, 0);
	return (0);
}