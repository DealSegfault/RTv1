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
			x += 2;
			++i;
		}
		y += 2;
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
	// printf("(%d -- %d) = ", LARGEUR * ALIASING, HAUTEUR * ALIASING);
	// printf("(%d -- %d)\n", LARGEUR * ALIASING / RES, HAUTEUR * ALIASING / RES);
	while (i < NB_THREADS)
	{
		th_e[i] = copy_rt(e);
		th_e[i]->thread.h = HAUTEUR * ALIASING;
		th_e[i]->thread.w = LARGEUR * ALIASING;
		th_e[i]->thread.y = ((th_e[i]->thread.h / RES) / NB_THREADS) * i;
		th_e[i]->thread.max_y = th_e[i]->thread.y + ((th_e[i]->thread.h / RES) / NB_THREADS);
		
		// printf("(%.1f - %.1f)\n", th_e[i]->thread.y, th_e[i]->thread.max_y);
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
	// printf("\n");
	i = 0;
	while (i < NB_THREADS)
	{
		pthread_join(th[i], NULL);
		++i;
	}
    return (th_e);
}