/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balvyn-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 21:37:34 by balvyn-s          #+#    #+#             */
/*   Updated: 2019/02/10 22:10:15 by balvyn-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void init_low(t_delta *new, int *yi, t_line *l)
{
	new->dx = l->end->x - l->start->x;
	new->dy = l->end->y - l->start->y;
	*yi = 1;
	if (new->dy < 0)
	{
		*yi = -1;
		new->dy = -(new->dy);
	}
	new->d = 2 * new->dy - new->dx;
	new->x = l->start->x;
	new->y = l->start->y;
}

int put_line_low(t_line *l, t_fdf *fdf)
{
	t_delta new;
	t_point *point;
	int yi;

	init_low(&new, &yi, l);
	while (new.x <= l->end->x)
	{
		if (!(point = get_simple_point(new.x, new.y, 0, fdf)))
			return (1);
		if (new.x < WIN_WIDTH &&new.y<WIN_HEIGHT &&new.x> 0 && new.y > 0)
			fdf->img.data[new.y *WIN_WIDTH + new.x] =
				get_color(point, l->start, l->end);
		if (new.d > 0)
		{
			new.y += yi;
			new.d -= 2 * new.dx;
		}
		new.d += 2 * new.dy;
		new.x++;
		free(point);
	}
	free(l);
	return (0);
}

void init_high(t_delta *new, int *xi, t_line *l)
{
	new->dx = l->end->x - l->start->x;
	new->dy = l->end->y - l->start->y;
	*xi = 1;
	if (new->dx < 0)
	{
		*xi = -1;
		new->dx = -(new->dx);
	}
	new->d = 2 * new->dx - new->dy;
	new->x = l->start->x;
	new->y = l->start->y;
}

int put_line_high(t_point *a, t_point *b, t_fract *f)
{
	int dx;
	int dy;

  dx = b->x - a->x;
  dy = b->y - a->y;
  int xi = 1
  if (dx < 0)
  {
    xi = -1
    dx = -dx
  }
  int D = 2*dx - dy
  int x = x0
  int y = a->y;
  while (y++ < b->y)
   {
	   fdf->img.data[new.y *WIN_WIDTH + new.x] =
				get_color(point, l->start, l->end);
    if (D > 0)
	{
       x = x + xi
       D = D - 2*dy
    }
    D = D + 2*dx
   }
	return (0);
}

int put_line(t_point *a, t_point *b, t_fract *f)
{
	int ret;

	ret = 0;
	if (ft_abs(b->y - a->y) < ft_abs(b->x - a->x))
	{
		if (a->x > b->x)
			swap_points(a, b);
		ret = put_line_low(a, b, f);
		return (ret);
	}
	else
	{
		if (a->y > b->y)
			swap_points(l);
		ret = put_line_high(l, fdf);
		return (ret);
	}
}
