#include "fractol.h"

int ft_putter_jul(t_fract *f)
{
	f->a_r = 1.0 * f->x / f->zoom + f->xx;
	f->a_i = 1.0 * f->y / f->zoom + f->yy;
	f->i = 0;
	while (f->i < f->iternum && f->a_r * f->a_r + f->a_i * f->a_i < 4)
	{
		f->b_r = 1.0 * (f->a_r * f->a_r - f->a_i * f->a_i - 0.9);
		f->b_i = 2.0 * f->a_r * f->a_i;
		f->a_r = 1.0 * (f->b_r + f->c_r / WINSIZE);
		f->a_i = 1.0 * (f->b_i + f->c_i / WINSIZE);
		f->i++;
	}
	if (f->i == f->iternum)
		f->img.data[f->y * WINSIZE + f->x] = 0x000000;
	else
		f->img.data[f->y * WINSIZE + f->x] = f->color * f->i;
	return (0);
}

void *julia(void *fr)
{
	t_fract *f;

	f = fr;
	while (f->y < f->y_max)
	{
		f->x = 0;
		while (f->x < WINSIZE)
		{
			ft_putter_jul(f);
			f->x++;
		}
		f->y++;
	}
	return (f);
}

int ft_init_jl(t_fract *f)
{
	if (f->init)
	{
		f->jl_moves = 0;
		f->xx = -2;
		f->yy = -2;
		f->color = 0xC8FFFD;
		f->c_r =  105;
		f->c_i = 116;
		f->zoom = WINSIZE / 4;
		f->iternum = 50;
	}
	ft_j_pthread(f);
	return (0);
}

void ft_j_pthread(t_fract *f)
{
	pthread_t thread[THREADS];
	t_fract fract[THREADS];
	int i;

	i = 0;
	while (i < THREADS)
	{
		ft_memcpy((void *)(&fract[i]), (void *)f, sizeof(t_fract));
		fract[i].y = THREAD_HEIGHT * i;
		fract[i].y_max = THREAD_HEIGHT * (i + 1);
		if (pthread_create(&thread[i], NULL, julia, &fract[i]) != 0)
			exit(0);
		i++;
	}
	while (i--)
		pthread_join(thread[i], NULL);
	mlx_put_image_to_window(f->mlx, f->win, f->img.img_ptr, 0, 0);
}
