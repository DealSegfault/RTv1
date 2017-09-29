/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalit <mhalit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/07 05:21:15 by mhalit            #+#    #+#             */
/*   Updated: 2017/09/20 22:29:22 by mparigi          ###   ########.fr       */
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
    while (x <= max_x)
    {
        while (y <= max_y)
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
}

void	mlx_pixel(int x, int y, t_rt *e, int color)
{
	int		pos;

	if (x < LARGEUR && y < HAUTEUR)
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
	if (e->scene.filters == 4)
		fl_stereoscopie(e);
	if (e->scene.filters == 6)
		fl_motionblur(e);
}

void	frame(t_rt *e)
{
	t_rt		**th_e;
	int			i;
	int			i2;
	int			x;
	int			y;

	e->frame++;
	// printf("%d\n", e->frame);
	matrix_init(e);
	th_e = launch_thread(e);
	i = 0;
	i2 = 0;

	while (i < NB_THREADS)
	{
		y = th_e[i]->thread.y / ALIASING;
		// printf("%f\n", th_e[i]->thread.y/ ALIASING);
		// printf("%f \n\n", th_e[i]->thread.max_y/ ALIASING);
		while (y < th_e[i]->thread.max_y / ALIASING)
		{
			x = 0;
			while (x < th_e[i]->thread.w / ALIASING)
			{
				// if (e->scene.filters == 5)
					pixel_to_image(x, y, e, ret_colors(th_e[i]->thread.colors[i2]));
				// else
				// 	pixel_to_image(x, y, e, ret_colors(th_e[i]->thread.colors[i2]));				
				// mlx_pixel(x, y, e, ret_colors(th_e[i]->thread.colors[i2]));
				++x;
				++i2;
			}
			++y;
		}
		i2 = 0;
		++i;
	}
	filters(e);
	free(th_e);
	mlx_put_image_to_window(INIT, WIN, IMG, 0, 0);
	disp_cam(e, 0x00FFFFFF);
}
