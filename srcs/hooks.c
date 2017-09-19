/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocojeda- <ocojeda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 17:18:21 by bbeldame          #+#    #+#             */
/*   Updated: 2017/08/17 21:26:22 by rlecart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			ambient(int keycode, t_rt *e)
{
	if (keycode == LSHIFT || keycode == SPACE)
	{
		AMBIENT_LIGHT += (keycode == LSHIFT) ? 10 : -10;
		frame(e);
	}
}

void			choose_filters(int keycode, t_rt *e)
{
	if (keycode >= 18 && keycode <= 21)
	{
		if (keycode == KEY_1)
			e->scene.filters = 0;
		if (keycode == KEY_2)
			e->scene.filters = 1;
		if (keycode == KEY_3)
			e->scene.filters = 2;
		if (keycode == KEY_4)
			e->scene.filters = 3;
		frame(e);
	}
}

void	resolution(int keycode, t_rt *e)
{
	if (keycode == PLUS || keycode == MINUS)
	{
		// e->scene.cam.fov += (keycode == PLUS) ? 2 : -2;
		RES += (keycode == PLUS) ? 2 : -2;
		if (RES < 1)
			RES = 1;
		if (RES > 200)
			RES = 200;
		frame(e);
	}
}

void	udlr_(int keycode, t_rt *e)
{
	if (keycode == LEFT || keycode == RIGHT || keycode == UP || keycode == DOWN)
	{
		if (keycode <= RIGHT)
			CPOS.x += ((keycode == LEFT) ? -60 / RES: 60 / RES);
		else
			CPOS.y += ((keycode == UP) ? -60 / RES : 60 / RES);
		//printf("Dir {%f %f %f}\n", CDIR.x, CDIR.y, CDIR.z);
		//printf("POS {%f %f %f}\n\n", CPOS.x, CPOS.y, CPOS.z);
		frame(e);
	}
}

void	wasd_(int keycode, t_rt *e)
{
	if (keycode == KEY_W || keycode == KEY_A || keycode == KEY_S || keycode == KEY_D)
	{
		if (keycode == KEY_W || keycode == KEY_S)
			e->scene.cam.rotx += ((keycode == KEY_S) ? 5 : -5);
		else
			e->scene.cam.roty += ((keycode == KEY_D) ? 5 : -5);
	//	printf("Dir {%f %f %f}\n", CDIR.x, CDIR.y, CDIR.z);
		//printf("POS {%f %f %f}\n\n", CPOS.x, CPOS.y, CPOS.z);
		frame(e);
	}
}

void			exportimg(int keycode, t_rt *e)
{
	t_file 		export;
	int			pos;

	if (keycode == 50)
	{
		if (!(export.fdp = open("first.ppm", O_WRONLY | O_CREAT, 00755)))
			return ;
		ft_putstr_fd("P6\n", export.fdp);
		ft_putnbr_fd(LARGEUR, export.fdp); 
		ft_putstr_fd(" ", export.fdp);
		ft_putnbr_fd(HAUTEUR, export.fdp);
		ft_putstr_fd("\n255\n", export.fdp);
		export.haut = -1;
		while (++export.haut < HAUTEUR)
		{
			export.larg = -1;
			while (++export.larg < LARGEUR)
			{
				pos = (export.larg * e->mlx.bpp / 8 + export.haut * e->mlx.size_l);
				write(export.fdp, &DATA[pos + 2], 1);
				write(export.fdp, &DATA[pos + 1], 1);
				write(export.fdp, &DATA[pos], 1);
			}
		}
		close(export.fdp);
	}
}

void			numeric_(int keycode, t_rt *e)
{
	if (keycode == 91 || keycode == 84)
	{
		CPOS.z += (keycode == 91) ? 100 : -100;
		frame(e);
	}
}

int				key_hook(int keycode, t_rt *e)
{
	if (keycode == ESC)
		exit(42);
	// if (keycode == 45)
	// 	new_rt();
	// if (keycode == 31)
	// 	show_settings(e);
	udlr_(keycode, e);
	wasd_(keycode, e);
	numeric_(keycode, e);
	resolution(keycode, e);
	exportimg(keycode, e);
	ambient(keycode, e);
	//Add CPOS.z + CDIR.z
	ft_putnbr(keycode);
	choose_filters(keycode, e);
	return (0);
}