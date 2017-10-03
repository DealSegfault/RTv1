/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparigi <mparigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 22:26:17 by mhalit            #+#    #+#             */
/*   Updated: 2017/09/29 08:56:56 by mparigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color			ft_average(t_color c1, t_color c2, t_color c3, t_color c4)
{
	t_color final;

	final.r = (c1.r + c2.r + c3.r + c4.r) / 4;
	final.g = (c1.g + c2.g + c3.g + c4.g) / 4;
	final.b = (c1.b + c2.b + c3.b + c4.b) / 4;
	return (final);
}

void			*drawlinex2(void *arg)
{
	t_rt		*e;
	int			y;
	int			x;
	int			i;

	e = (t_rt *)arg;
	e->thread.colors =
	malloc((e->thread.h * e->thread.w + 1) * sizeof(t_color));
	y = e->thread.y;
	i = -1;
	while (y < e->thread.max_y)
	{
		x = 0;
		while (x < e->thread.w)
		{
			e->thread.colors[++i] = ft_average(raytrace(x, y, e),
			raytrace(x + 1, y, e), raytrace(x, y + 1, e),
			raytrace(x + 1, y + 1, e));
			if (e->scene.filters == 5)
				e->thread.colors[i] = fl_cartoon(e->thread.colors[i]);
			x += ALIASING;
		}
		y += ALIASING;
	}
	return (NULL);
}

void			*drawline(void *arg)
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

t_rt			**launch_thread(t_rt *e)
{
	int			i;
	pthread_t	th[NB_THREADS];
	t_rt		**th_e;

	if (!(th_e = (t_rt **)malloc(NB_THREADS * sizeof(t_rt *))))
		return (NULL);
	i = -1;
	while (++i < NB_THREADS)
	{
		th_e[i] = copy_rt(e);
		THREAD.h = HAUTEUR * ALIASING;
		THREAD.w = LARGEUR * ALIASING;
		THREAD.h /= RES;
		THREAD.w /= RES;
		THREAD.y = ((THREAD.h) / NB_THREADS) * i;
		THREAD.max_y = THREAD.y + ((THREAD.h) / NB_THREADS);
		if (ALIASING == 1)
			pthread_create(&th[i], NULL, drawline, (void *)th_e[i]);
		else
			pthread_create(&th[i], NULL, drawlinex2, (void *)th_e[i]);
	}
	i = -1;
	while (++i < NB_THREADS)
		pthread_join(th[i], NULL);
	return (th_e);
}
