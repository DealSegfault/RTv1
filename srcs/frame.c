/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparigi <mparigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/07 05:21:15 by mhalit            #+#    #+#             */
/*   Updated: 2017/09/29 12:01:04 by mparigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			pixel_to_image(int x, int y, t_rt *e, int color)
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
			if ((x >= 0 && y >= 0) || (x < RES_W && y < RES_H))
				mlx_pixel(x, y, e, color);
			y++;
		}
		y = start_y;
		x++;
	}
}

void			mlx_pixel(int x, int y, t_rt *e, int color)
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

void			filters(t_rt *e)
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

void			dname(t_rt *e, t_rt **th_e, int i)
{
	int			inc;

	inc = -1;
	while (++inc < e->scene.nbr_obj)
	{
		if (th_e[i]->scene.obj[inc].is_disp && (!e->scene.obj[inc].is_disp
		|| e->scene.obj[inc].last_pos.x < th_e[i]->scene.obj[inc].last_pos.x))
		{
			e->scene.obj[inc].is_disp = 1;
			e->scene.obj[inc].last_pos = th_e[i]->scene.obj[inc].last_pos;
		}
	}
}

void			frame(t_rt *e)
{
	t_rt		**th_e;
	int			i;
	int			i2;
	t_norme		n;

	e->frame++;
	matrix_init(e);
	th_e = launch_thread(e);
	i = -1;
	while (++i < NB_THREADS)
	{
		n.y = (th_e[i]->thread.y / ALIASING) - 1;
		i2 = -1;
		while (++n.y < th_e[i]->thread.max_y / ALIASING)
		{
			n.x = -1;
			while (++n.x < th_e[i]->thread.w / ALIASING)
				pixel_to_image(n.x, n.y, e, ret_colors(CTHREAD));
		}
		dname(e, th_e, i);
	}
	filters(e);
	free(th_e);
	mlx_put_image_to_window(INIT, WIN, IMG, 0, 0);
	disp_cam(e, 0x00FFFFFF);
}
