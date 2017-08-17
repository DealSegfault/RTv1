/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supersampler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocojeda- <ocojeda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 09:45:23 by ocojeda-          #+#    #+#             */
/*   Updated: 2017/08/17 17:41:49 by ocojeda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	anti_aliasing_off(t_rt *env)
{
	int x;
	int y;

	y = 0;
	while (y < HAUTEUR)
	{
		x = 0;
		while (x < LARGEUR)
		{
			mlx_pixel(x, y, env, ret_colors(raytrace(x, y, env)));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(INIT, WIN, IMG, 0, 0);
}

unsigned int *anti_aliasing_img_creator(t_rt *env, unsigned int *img_temp)
{
	int x;
	int y;
	

	img_temp = (unsigned int *)malloc(sizeof(unsigned int) * (W * H));
	y = 0;
	x = 0;
	while (y < H)
	{
		x = 0;
		while (x < W)
		{
			img_temp[x + y * W] = ret_colors(raytrace(x, y, env));
			x++;
		}
		y++;
	}
	return (img_temp);
}

void	anti_aliasing_on(t_rt *env, unsigned int *img_temp)
{
	int x;
	int y;
	int x1;
	int y1;

	if((img_temp = anti_aliasing_img_creator(env, NULL)))
	{
		y = 0;
		y1 = 0;
		while (y < H / 2)
		{
			x = 0;
			x1 = 0;
			while (x < W / 2)
			{
				mlx_pixel(x, y, env, AVERAGE(AVERAGE
				(img_temp[x1 + y1 * W],
				img_temp[(x1 + 1) + (y1 * W)]),
				AVERAGE(img_temp[x1 + (y1 + 1) * W],
				img_temp[(x1 + 1) + (y1 + 1) * W])));
				x1 += 2;
				x++;
			}
			y++;
			y1 += 2;
		}
		free(img_temp);
	}
}

void	anti_supersampler(t_rt *env)
{
	int		x;
	int		x1;

	x = 0;
	x1 = LARGEUR * HAUTEUR;
	while (x < x1)
	{
		((unsigned int *)env->mlx.data)[x] = env->img_temp[x];
		x++;
	}
}

void	super_sampler(t_rt *env)
{
	int		x;
	int		y;
	int		x1;
	int		y1;

	y = 0;
	y1 = 0;
	while (y < HAUTEUR / 2)
	{
		x = 0;
		x1 = 0;
		while (x < LARGEUR / 2)
		{
			((unsigned int *)env->mlx.data)[x + y * LARGEUR / 2] = AVERAGE(
				AVERAGE(env->img_temp[x1 + y1 * LARGEUR],
					env->img_temp[(x1 + 1) + (y1 * LARGEUR)]),
				AVERAGE(env->img_temp[x1 + (y1 + 1) * LARGEUR],
					env->img_temp[(x1 + 1) + (y1 + 1) * LARGEUR]));
			x1 += 2;
			x++;
		}
		y++;
		y1 += 2;
	}
}
