/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/07 05:21:15 by mhalit            #+#    #+#             */
/*   Updated: 2017/08/17 21:21:50 by rlecart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void    pixel_to_image(int x, int y, t_rt *e, int color)
{
    int max_x;
    int max_y;
    int start_y;

    x = x * RES;
    y = y * RES;
    start_y = y;
    max_x = x + RES;
    max_y = y + RES;
    while (x < max_x)
    {
        while (y < max_y)
        {
            if ((x >= 0 && y >= 0 ) || (x < RES_W && y < RES_H ))
            {
                // if (RES > 10 && (x + 1 == max_x || y + 1 == max_y))
                //     mlx_pixel(x, y, e, 0x333333);
                // else
                    mlx_pixel(x, y, e, color);
            }
            y++;
        }
        y = start_y;
        x++;
    }
    if (color)
    {}
}

void	mlx_pixel(int x, int y, t_rt *e, int color)
{
	int		pos;

	if (x && y && x < LARGEUR && y < HAUTEUR)
	{
		pos = x * 4 + y * e->mlx.size_l;
		e->mlx.data[pos] = color;
		e->mlx.data[pos + 1] = color >> 8;
		e->mlx.data[pos + 2] = color >> 16;
	}
}

void	filters(t_rt *e)
{
	if (e->scene.filters == 1)
		fl_sepia_apply(e);
	if (e->scene.filters == 2)
		fl_black_and_white(e);
	if (e->scene.filters == 3)
		fl_revers(e);
}

void	frame(t_rt *e)
{

	t_rt		**th_e;
	int			i;
	int			x;
	int			y;

	th_e = launch_thread(e);
	i = 0;
	while (i < NB_THREADS)
	{
		y = i;
		while (y < HAUTEUR /RES)
		{
			x = 0;
			while (x < LARGEUR/ RES)
			{
				pixel_to_image(x, y, e,
				ret_colors(th_e[i]->thread.colors[x + ((y / NB_THREADS) * RES_W)]));
				++x;
			}
			y += NB_THREADS;
		}
		++i;
	}
	filters(e);
	// free(th_e);
	mlx_put_image_to_window(INIT, WIN, IMG, 0, 0);
}

// void	frame(t_rt *e)
// {
// 	IMG = mlx_new_image(INIT, LARGEUR, HAUTEUR);
// 	e->mlx.data = mlx_get_data_addr(IMG, &e->mlx.bpp, &e->mlx.size_l,
// 		&e->mlx.endian);
// 	if (SS == 1)
// 		anti_aliasing_off(e);
// 	else
// 		anti_aliasing_on(e, NULL);
// 	filters(e);
// 	mlx_put_image_to_window(INIT, WIN, IMG, 0, 0);
// }
