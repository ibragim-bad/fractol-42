#include "../include/fractol.h"


int		ft_mlx(t_fract *f)
{
	if (f->img.img_ptr)
		mlx_destroy_image(f->mlx, f->img.img_ptr);
	if (!(f->img.img_ptr = mlx_new_image(f->mlx, WINSIZE, WINSIZE)))
		return (-1);
	ft_mndb(f);
	return (0);
}

int		ft_init (char *av, t_fract *f)
{
	if (!(f = (t_fract *)malloc(sizeof(t_fract))))
		return(-1);
	f->img.img_ptr = NULL;
	f->win = NULL;
	f->mlx = NULL;
	f->mlx = mlx_init();
	f->win = mlx_new_window(f->mlx, WINSIZE, WINSIZE, "fractol");
	if (av[0] == 's')
		return (-1);
	ft_mlx(f);
	mlx_key_hook(f->win, ft_key, (void *)f);
//	mlx_mouse_hook(f->win, ft_mouse, (void *)f);
	mlx_loop(f->mlx);
	return (0);
}


int		main(int ac, char *av[])
{
	t_fract	*f;

	f = NULL;
	if (ac == 2)
		ft_init(av[1], f);
	else
		write(1, "error\n", 7);
	return (0);
}