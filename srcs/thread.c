/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 22:26:17 by mhalit            #+#    #+#             */
/*   Updated: 2017/08/28 22:26:31 by mhalit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"


t_color		ft_average(t_color c1, t_color c2, t_color c3, t_color c4)
{
	t_color final;

	final.r = (c1.r + c2.r + c3.r + c4.r) / 4;
	final.g = (c1.g + c2.g + c3.g + c4.g) / 4;
	final.b = (c1.b + c2.b + c3.b + c4.b) / 4;
	return (final);
}

float	cartoon_color(float color)
{
	if (color < 15)
		color = 30;
	else if (color < 75)
		color = 75;
	else if (color < 120)
		color = 120;
	else if (color < 220)
		color = 220;
	else if (color < 255)
		color = 255;
	return (color);
}

t_color	fl_cartoon(t_color color)
{
	color.r = cartoon_color(color.r);
	color.g = cartoon_color(color.g);
	color.b = cartoon_color(color.b);
	return (color);
}

void	        *drawlinex2(void *arg)
{
	t_rt		*e;
	int			y;
	int			x;
	int			i;

	e = (t_rt *)arg;
	e->thread.colors =
	    malloc((e->thread.h * e->thread.w + 1) * sizeof(t_color));
	y = e->thread.y;
	i = 0;
	while (y < e->thread.max_y)
	{
		x = 0;
		while (x < e->thread.w)
		{
			e->thread.colors[i] = ft_average(	raytrace(x, y, e),
												raytrace(x + 1, y, e),
												raytrace(x, y + 1, e),
												raytrace(x + 1, y + 1, e));
			if (e->scene.filters == 5)
				e->thread.colors[i] = fl_cartoon(e->thread.colors[i]);
			x += ALIASING;
			++i;
		}
		y += ALIASING;
	}
	return (NULL);
}

void	        *drawline(void *arg)
{
	t_rt		*e;
	int			y;
	int			x;
	int			i;

	e = (t_rt *)arg;
	e->thread.colors =
	    malloc((e->thread.h * e->thread.w + 1) * sizeof(t_color));
	y = e->thread.y;
	i = 0;
	while (y < e->thread.max_y)
	{
		x = 0;
		while (x < e->thread.w)
		{
			e->thread.colors[i] = raytrace(x, y, e);
			if (e->scene.filters == 5)
				e->thread.colors[i] = fl_cartoon(e->thread.colors[i]);
			++x;
			++i;
		}
		++y;
	}
	return (NULL);
}

t_rt            **launch_thread(t_rt *e)
{
    int			i;
	pthread_t	th[NB_THREADS];
    t_rt		**th_e;

    if (!(th_e = (t_rt **)malloc(NB_THREADS * sizeof(t_rt *))))
        return (NULL);
	i = 0;
	while (i < NB_THREADS)
	{
		th_e[i] = copy_rt(e);
		th_e[i]->thread.h = HAUTEUR * ALIASING;
		th_e[i]->thread.w = LARGEUR * ALIASING;
		th_e[i]->thread.h /= RES;
		th_e[i]->thread.w /= RES;
		th_e[i]->thread.y = ((th_e[i]->thread.h) / NB_THREADS) * i;
		th_e[i]->thread.max_y = th_e[i]->thread.y + ((th_e[i]->thread.h) / NB_THREADS);
		if (ALIASING == 1)
			pthread_create(&th[i], NULL, drawline, (void *)th_e[i]);
		else if (ALIASING == 2)
			pthread_create(&th[i], NULL, drawlinex2, (void *)th_e[i]);
		else
		{
			ft_putstr("anti-aliasing != (0 || 1)");
			exit(42);
		}

		++i;
	}
	i = -1;
	while (++i < NB_THREADS)
		pthread_join(th[i], NULL);
    return (th_e);
}