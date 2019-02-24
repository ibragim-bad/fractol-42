#include "fractol.h"

t_point *new_point(int x, int y, t_fract *f)
{
	t_point *new;

	f->x += 0;
	new = (t_point *)malloc(sizeof(t_point));
	new->x = x;
	new->y = y;
	return (new);
}

void put_triangle(t_point *t, t_point *r, t_point *l, t_fract *f)
{
	drawline(l->x * f->zoom + f->xx, l->y * f->zoom + f->yy, t->x * f->zoom + f->xx, t->y * f->zoom + f->yy, f);
	drawline(l->x * f->zoom + f->xx, l->y * f->zoom + f->yy, r->x * f->zoom + f->xx, r->y * f->zoom + f->yy, f);
	drawline(t->x * f->zoom + f->xx, t->y * f->zoom + f->yy, r->x * f->zoom + f->xx, r->y * f->zoom + f->yy, f);
/*  	free(t);
	free(r);
	free(l);   */
}

void DrawTriangle(int level,
				  t_point *t, t_point *r, t_point *l, t_fract *f)
{
	t_point *l_mid;
	t_point *r_mid;
	t_point *b_mid;

/*  	l_mid = (t_point *)malloc(sizeof(t_point));
	r_mid = (t_point *)malloc(sizeof(t_point));
	b_mid = (t_point *)malloc(sizeof(t_point));  */
	// See if we should stop.
	if (level == 0)
	{
		// Fill the triangle.
		put_triangle(t, r, l, f);
		return;
	}
	else
	{
		// Find the edge midpoints.
		l_mid = new_point((t->x + l->x) / 2,
						  (t->y + l->y) / 2, f);
		r_mid = new_point(
			(t->x + r->x) / 2,
			(t->y + r->y) / 2, f);
		b_mid = new_point(
			(l->x + r->x) / 2,
			(l->y + r->y) / 2, f);

		// Recursively draw smaller triangles.
		DrawTriangle(level - 1,
					 t, l_mid, r_mid, f);
		DrawTriangle(level - 1,
					 l_mid, l, b_mid, f);
		DrawTriangle(level - 1,
					 r_mid, b_mid, r, f);
	}
}

int ft_init_srp(t_fract *f)
{
	if (f->init)
	{
		f->y = 0;
		f->x = 0;
		f->inverter = 1;
		f->black = 1;
		f->iternum = ITERNUM;
		f->y_max = WINSIZE;
		f->inverter = 1;
		f->black = 1;
		f->color = 0xC8FFFD;
		f->level = 10;
		f->zoom = 1;
		f->xx = 0;
		f->yy = 0;
	}
	return (0);
}

void *sierp(void *fr)
{
	t_point *l;
	t_point *r;
	t_point *t;
	t_fract *f;

	f = fr;
	f->img.img_ptr = mlx_new_image(f->mlx, WINSIZE, WINSIZE);
	f->img.data = (int *)mlx_get_data_addr(f->img.img_ptr, &f->img.bpp,
										   &f->img.size_l, &f->img.endian);
	l = (t_point *)malloc(sizeof(t_point));
	r = (t_point *)malloc(sizeof(t_point));
	t = (t_point *)malloc(sizeof(t_point));
	l = new_point(0, WINSIZE, f);
	r = new_point(WINSIZE, WINSIZE, f);
	t = new_point(WINSIZE / 2, 0, f);
	DrawTriangle(f->level, t, r, l, f);
	mlx_put_image_to_window(f->mlx, f->win, f->img.img_ptr, 0, 0);
	return (0);
}
/* 
void ft_srp_pthread(t_fract *f)
{
	pthread_t thread[THREADS];
	t_fract fract[THREADS];
	int i;

	f->img.img_ptr = mlx_new_image(f->mlx, WINSIZE, WINSIZE);
	f->img.data = (int *)mlx_get_data_addr(f->img.img_ptr, &f->img.bpp,
										   &f->img.size_l, &f->img.endian);
	i = 0;
	while (i < THREADS)
	{
		ft_memcpy((void *)(&fract[i]), (void *)f, sizeof(t_fract));
		fract[i].y = THREAD_HEIGHT * i;
		fract[i].y_max = THREAD_HEIGHT * (i + 1);
		if (pthread_create(&thread[i], NULL, sierp, &fract[i]) != 0)
			exit(0);
		i++;
	}
	while (i--)
		pthread_join(thread[i], NULL);
	mlx_put_image_to_window(f->mlx, f->win, f->img.img_ptr, 0, 0);
} */