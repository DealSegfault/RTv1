/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supersampler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfaure <tfaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 09:45:23 by ocojeda-          #+#    #+#             */
/*   Updated: 2017/08/21 13:07:30 by tfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	anti_aliasing_off(t_rt *e)
{
	int x;
	int y;

	y = 0;
	while (y < HSS)
	{
		x = 0;
		while (x < WSS)
		{
			mlx_pixel(x, y, e, ret_colors(raytrace(x, y, e)));
			x += 1;
		}
		y += 1;
	}
	mlx_put_image_to_window(INIT, WIN, IMG, 0, 0);
}

unsigned int *anti_aliasing_img_creator(t_rt *e, unsigned int *img_temp)
{
	int x;
	int y;
	
	img_temp = (unsigned int *)malloc(sizeof(unsigned int) * (WSS * HSS));
	y = 0;
	x = 0;
	while (y < HSS)
	{
		x = 0;
		while (x < WSS)
		{
			img_temp[x + y * WSS] = ret_colors(raytrace(x, y, e));
			x += 1;
		}
		y += 1;
	}
	return (img_temp);
}

void	anti_aliasing_on(t_rt *e, unsigned int *img_temp)
{
	int x;
	int y;
	int x1;
	int y1;

	if((img_temp = anti_aliasing_img_creator(e, NULL)))
	{
		y = 0;
		y1 = 0;
		while (y < HSS / 2)
		{
			x = 0;
			x1 = 0;
			while (x < WSS / 2)
			{
				mlx_pixel(x, y, e, AVERAGE(AVERAGE
				(img_temp[x1 + y1 * WSS],
				img_temp[(x1 + 1) + (y1 * WSS)]),
				AVERAGE(img_temp[x1 + (y1 + 1) * WSS],
				img_temp[(x1 + 1) + (y1 + 1) * WSS])));
				x1 += 1;
			}
			y1 += 1;
		}
		free(img_temp);
	}
}

// void	anti_supersampler(t_rt *e)
// {
// 	int		x;
// 	int		x1;

// 	x = 0;
// 	x1 = WSS * HSS;
// 	while (x < x1)
// 	{
// 		((unsigned int *)e->mlx.data)[x] = e->img_temp[x];
// 		x += 1;
// 	}
// }

// void	super_sampler(t_rt *e)
// {
// 	int		x;
// 	int		y;
// 	int		x1;
// 	int		y1;

// 	y = 0;
// 	y1 = 0;
// 	while (y < HSS / 2)
// 	{
// 		x = 0;
// 		x1 = 0;
// 		while (x < WSS / 2)
// 		{
// 			((unsigned int *)e->mlx.data)[x + y * WSS / 2] = AVERAGE(
// 				AVERAGE(e->img_temp[x1 + y1 * WSS],
// 					e->img_temp[(x1 + 1) + (y1 * WSS)]),
// 				AVERAGE(e->img_temp[x1 + (y1 + 1) * WSS],
// 					e->img_temp[(x1 + 1) + (y1 + 1) * WSS]));
// 			x1 += 1;
// 		}
// 		y1 += 1;
// 	}
// }