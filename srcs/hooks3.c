/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparigi <mparigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 11:34:21 by mhalit            #+#    #+#             */
/*   Updated: 2017/10/01 19:43:10 by mparigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				ft_close(void *param)
{
	param = NULL;
	exit(42);
	return (0);
}

int				no_event(void *param)
{
	t_rt	*e;

	e = (t_rt *)param;
	key(e);
	return (OK);
}

int				calcul_res(t_rt *e, int limit)
{
	int res;
	int air;

	air = LARGEUR * HAUTEUR;
	res = 1;
	if (ALIASING == 2)
		limit /= 2;
	while ((air / res) > limit)
		res++;
	return (res);
}

void			auto_res(int keycode, t_rt *e)
{
	int		average_res;

	if (keycode != PAGE_UP && keycode != PAGE_DOWN && nbrs_keys(e) >= 1)
	{
		average_res = calcul_res(e, 125000);
		if (average_res > RES)
			RES = average_res;
	}
}
