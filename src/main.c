#include "fractol.h"

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

int ft_mlx(t_fract *f)
{
	if (f->img.img_ptr)
		mlx_destroy_image(f->mlx, f->img.img_ptr);
	if (!(f->img.img_ptr = mlx_new_image(f->mlx, WINSIZE, WINSIZE)))
		return (-1);
	f->img.data = (int *)mlx_get_data_addr(f->img.img_ptr, &f->img.bpp,
										   &f->img.size_l, &f->img.endian);
	if (f->type == 0)
		ft_init_mndb(f);
	if (f->type == 1)
		ft_init_duck(f);
	if (f->type == 2)
		ft_init_jl(f);
	if (f->type == 3)
		ft_init_random(f);
	return (0);
}

int ft_init(char *av, t_fract *f)
{
	f->img.img_ptr = NULL;
	f->win = NULL;
	f->mlx = NULL;
	f->mlx = mlx_init();
	f->win = mlx_new_window(f->mlx, WINSIZE, WINSIZE, "fractol");
	f->type = -1;
	f->init = 1;
	if (ft_strequ(av, "mandelbrot"))
		f->type = 0;
	else if (ft_strequ(av, "duck"))
		f->type = 1;
	else if (ft_strequ(av, "julia"))
		f->type = 2;
	else if (ft_strequ(av, "random"))
		f->type = 3;
	if (f->type == -1)
		ft_error(1, f);
	ft_mlx(f);
	mlx_hook(f->win, 2, 5, ft_key, f);
	mlx_hook(f->win, 4, 5, ft_mouse, f);
	mlx_hook(f->win, 6, (1L << 6), ft_jl_moves, f);
	mlx_hook(f->win, 17, (1L << 5), finish, f);
	mlx_loop(f->mlx);
	return (0);
}

int main(int ac, char *av[])
{
	t_fract *f;

	f = NULL;
	if (!(f = (t_fract *)malloc(sizeof(t_fract))))
		return (-1);
	if (ac >= 2)
		while (ac-- > 1)
			ft_init(av[ac], f);
	else
		ft_error(1, f);
	return (0);
}
