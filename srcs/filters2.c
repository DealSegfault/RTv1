/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlecart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 17:21:08 by rlecart           #+#    #+#             */
/*   Updated: 2017/09/27 13:14:59 by mhalit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void		fl_stereoscopie(t_rt *e)
{
	int		i;

	i = 0;
	while (i < (LARGEUR * HAUTEUR * 4))
	{
		DATA[i + 1 - 40 - (LARGEUR * 4) * 10] = DATA[i + 1];
		DATA[i + 1] = 0;
		DATA[i - 40 - (LARGEUR * 4) * 10] = DATA[i];
		DATA[i] = 0;
		i += 4;
	}
}

int			ft_average_blur(t_rt *e, int i, int size)
{
	int		x;
	int		y;
	int		average;
	int		tmp;

	x = 0;
	average = 0;
	while (x < (size * 4))
	{
		y = 0;
		while (y < (size * 4))
		{
			tmp = i + x + (y * SIZE_L);
			average += (DATA[tmp]);
			if (DATA[tmp] < 0)
				average += 256;
			y += 4;
		}
		x += 4;
	}
	average /= size * size;
	return (average);
}

void		fl_motionblur(t_rt *e)
{
	int		i;

	i = 0;
	while (i < (HAUTEUR * SIZE_L))
	{
		DATA[i] = ft_average_blur(e, i, 5);
		i++;
	}
}
