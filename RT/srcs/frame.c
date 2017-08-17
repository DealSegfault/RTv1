/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocojeda- <ocojeda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/07 05:21:15 by mhalit            #+#    #+#             */
/*   Updated: 2017/08/17 16:36:54 by ocojeda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	mlx_pixel(int x, int y, t_rt *env, int color)
{
	int		pos;

	if (x && y && x < LARGEUR && y < HAUTEUR)
	{
		pos = x * 4 + y * env->mlx.size_l;
		env->mlx.data[pos] = color;
		env->mlx.data[pos + 1] = color >> 8;
		env->mlx.data[pos + 2] = color >> 16;
	}
}

void	frame(t_rt *env)
{
	IMG = mlx_new_image(INIT, LARGEUR, HAUTEUR);
	env->mlx.data = mlx_get_data_addr(IMG, &env->mlx.bpp, &env->mlx.size_l,
		&env->mlx.endian);
	if (SS == 1)
		anti_aliasing_off(env);
	else
		anti_aliasing_on(env);
	mlx_put_image_to_window(INIT, WIN, IMG, 0, 0);
}