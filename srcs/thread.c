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

void	        *drawline(void *arg)
{
	t_rt		*e;
	int			x;
	int			i;

	e = (t_rt *)arg;
	e->thread.colors =
	    malloc((HAUTEUR * LARGEUR + 1) * sizeof(t_color));
	i = 0;
	while (e->thread.y < RES_H)
	{
		x = 0;
		while (x < RES_W)
		{
			e->thread.colors[i] = raytrace(x, e->thread.y, e);
			++x;
			++i;
		}
		e->thread.y += NB_THREADS;
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
		th_e[i]->thread.y = i;
		pthread_create(&th[i], NULL, drawline, (void *)th_e[i]);
		++i;
	}
	i = 0;
	while (i < NB_THREADS)
	{
		pthread_join(th[i], NULL);
		++i;
	}
    return (th_e);
}