/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 00:09:53 by mhalit            #+#    #+#             */
/*   Updated: 2017/08/17 21:21:50 by rlecart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	display_args(void)
{
	ft_putstr("\nusage: rtv1 [-s source] [-w width] [-h height]\n");
	ft_putstr("-s : Set the specified source file\n");
	ft_putstr("-w : Width of the window, default 500px\n");
	ft_putstr("-h : Height of the window, default 500px\n");
	ft_putstr("--help : Show help\n");
	ft_putstr("-a : Set the antialiasing technique to the image\n");
	exit(42);
}


static void		key_init(t_rt *e)
{
	e->keys.key_up = 0;
	e->keys.key_down = 0;
	e->keys.key_right = 0;
	e->keys.key_left = 0;
	e->keys.key_pagup = 0;
	e->keys.key_pagdwn = 0;
	e->keys.key_w = 0;
	e->keys.key_a = 0;
	e->keys.key_s = 0;
	e->keys.key_d = 0;
	e->keys.key_rotx_right = 0;
	e->keys.key_rotx_left = 0;
	e->keys.key_roty_right = 0;
	e->keys.key_roty_left = 0;
	e->keys.key_plus = 0;
	e->keys.key_minus = 0;
	// e->scene.diff = 0.6;
	// e->scene.spec = 0.2;
	e->scene.selected = -1;
}

void		init_rt(t_rt *e)
{
	e->mlx.init = mlx_init();
	LARGEUR = 1024;
	HAUTEUR = 768;
	RES = 5;
	ALIASING = 1;
	e->scene.nbr_obj = 0;
	e->scene.nbr_light = 0;
	e->scene.nbr_tot = 0;
	e->scene.ambient = 0.2;
	e->scene.obj = (t_obj *)malloc(sizeof(t_obj) * MAXOBJ);
	e->scene.lights = (t_light *)malloc(sizeof(t_light) * MAXLIGHT);
	e->scene.supersampling = 1;
	e->scene.filters = 0;
	e->scene.selected = -1;
	e->scene.cam.aspect = (float)LARGEUR / (float)HAUTEUR;
	key_init(e);
}

void ft_start_rt(t_rt *e)
{
	if (!HAUTEUR || !LARGEUR)
		exit(0);
	e->mlx.window = mlx_new_window(e->mlx.init, e->file.larg, e->file.haut, "RT Again");
	IMG = mlx_new_image(INIT, LARGEUR, HAUTEUR);
	e->mlx.data = mlx_get_data_addr(IMG, &e->mlx.bpp, &e->mlx.size_l,
	&e->mlx.endian);
	frame(e);
	mlx_key_hook(WIN, key_hook, e);
	// mlx_hook(WIN, 2, 0, keypress, e);
	// mlx_hook(WIN, 3, 0, keyrelease, e);
	// mlx_hook(WIN, 17, 0, ft_close, NULL);
	// mlx_mouse_hook(WIN, select_obj, e);
	//mlx_mouse_hook(WIN, mouse_hook, e);
	
	mlx_loop(INIT);
}
          
int			main(int argc, char **argv)
{
	t_rt	*e;

	e = (t_rt *)malloc(sizeof(t_rt));
	init_rt(e);
	if (argc > 2)
	{
		if (!parse_args(argv, argc, e))
			return (0);
		ft_start_rt(e);
	}
	else
		display_args();
	 	//ft_gtk_start(e, argc, argv);

	return (0);
}