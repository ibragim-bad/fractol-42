#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <math.h>
# include <pthread.h>
# include "../libft/libft.h"
# include "mlx.h"
# include <stdio.h>

# define WIN_WIDTH 800
# define WIN_HEIGHT 800
# define WINSIZE 850
# define ITERNUM 20
# define KEY_UP 0xff52
# define KEY_DOWN 0xff54
# define KEY_LEFT 0xff51
# define KEY_RIGHT 0xff53
# define KEY_PLUS 0xffab
# define KEY_MINUS 0xffad
# define KEY_ESCAPE 0xff1b
# define MOUSE_LB 1
# define MOUSE_RB 3
# define MOUSE_SB 2
# define THREADS 4
# define THREAD_HEIGHT (WINSIZE / THREADS)

typedef struct	s_img
{
	void		*img_ptr;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
}				t_img;

typedef struct	s_fract
{
    void		*mlx;
	void		*win;
	t_img		img;
	int			i;
	double		a_r;
	double		a_i;
	double		b_r;
	double		b_i;
	double		c_r;
	double		c_i;
	double		d_r;
	double		d_i;
	double		xx;
	double		yy;
	int			x;
	int			y;
	int			y_max;
	int			color;
	double		zoom;
	int			iternum;
	int			inverter;
	int			black;
	int			noinit;
}               t_fract;

int		ft_putter(t_fract *f);
void	*mandelbrot(void *fr);
int		ft_init_mndb(t_fract *f);
int		ft_mndb(t_fract *f);
int     ft_key(int key, t_fract *f);
int		ft_mlx(t_fract *f);
int		ft_mouse(int button, int x, int y, void *f);

#endif