/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 10:14:25 by mhalit            #+#    #+#             */
/*   Updated: 2017/09/27 13:13:52 by mhalit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				fl_sepia_apply(t_rt *e)
{
	size_t			i;
	unsigned int	max;
	unsigned char	*img;

	img = (unsigned char *)DATA;
	max = ((HAUTEUR * LARGEUR) * 4) - 4;
	i = 0;
	while (i < max)
	{
		img[i + 2] = FT_MIN((0.393 * img[i + 2]) +
			(0.769 * img[i + 1]) + (0.189 * img[i]), 255.0);
		img[i + 1] = FT_MIN((0.349 * img[i + 2]) +
				(0.686 * img[i + 1]) + (0.168 * img[i]), 255.0);
		img[i + 0] = FT_MIN((0.272 * img[i + 2]) +
				(0.534 * img[i + 1]) + (0.131 * img[i]), 255.0);
		i += 4;
	}
}

void				fl_black_and_white(t_rt *e)
{
	size_t			i;
	unsigned int	x;
	unsigned int	max;
	unsigned char	*img;

	img = (unsigned char *)DATA;
	max = ((HAUTEUR * LARGEUR) * 4) - 4;
	i = 0;
	while (i < max)
	{
		x = img[i + 2] + img[i + 1] + img[i];
		x /= 3;
		*((unsigned int *)(img + i)) = x | x << 8 | x << 16 | img[i + 3] << 24;
		i += 4;
	}
}

void				fl_revers(t_rt *e)
{
	size_t			i;
	unsigned int	max;
	unsigned char	*img;

	img = (unsigned char *)DATA;
	max = ((HAUTEUR * LARGEUR) * 4) - 4;
	i = 0;
	while (i < max)
	{
		img[i] = 255 - img[i];
		img[i + 1] = 255 - img[i + 1];
		img[i + 2] = 255 - img[i + 1];
		i += 4;
	}
}
