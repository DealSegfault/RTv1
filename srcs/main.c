/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalit <mhalit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 00:09:53 by mhalit            #+#    #+#             */
/*   Updated: 2017/09/20 20:02:47 by mparigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			display_args(void)
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
}

void			init_rt(t_rt *e)
{
	e->mlx.init = mlx_init();
	LARGEUR = 1024;
	HAUTEUR = 768;
	RES = 8;
	RES_BUFF = RES;
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
	key_init(e);
}

void			ft_start_rt(t_rt *e)
{
	if (!HAUTEUR || !LARGEUR)
		exit(0);
	e->mlx.window = mlx_new_window(e->mlx.init, e->file.larg, e->file.haut, "RT Again");
	IMG = mlx_new_image(INIT, LARGEUR, HAUTEUR);
	e->mlx.data = mlx_get_data_addr(IMG, &e->mlx.bpp, &e->mlx.size_l,
	&e->mlx.endian);
	frame(e);
	mlx_hook(WIN, 2, 0, keypress, e);
	mlx_hook(WIN, 3, 0, keyrelease, e);
	mlx_hook(WIN, 17, 0, ft_close, NULL);
	mlx_mouse_hook(WIN, select_obj, e);
	mlx_loop_hook(INIT, no_event, e);
	mlx_loop(INIT);
}

void			create_limits(t_rt *e)
{
	int			i;
	int			chk;

	i = 0;
	chk = 0;
	while (i < e->scene.nbr_obj)
	{
		e->COBJ.plimit_active = 0;
		e->COBJ.plimit_valid = 0;
		e->COBJ.plimit = NULL;
		if (e->COBJ.type == SPHERE && chk == 0)
		{
			e->COBJ.plimit_type = 0;
			e->COBJ.plimit_active = 1;
			e->COBJ.plimit = (t_obj *)malloc(sizeof(t_obj) + 1);
			e->COBJ.plimit->is_init = -1;
			e->COBJ.plimit->type = PLANE;
			e->COBJ.plimit->color = e->COBJ.color;
			e->COBJ.plimit->pos = vec_new3(750, 400, 300);
			e->COBJ.plimit->dir = vec_new3(0, 0, 0);
			e->COBJ.plimit->k = 0;
			e->COBJ.plimit->vector = vec_norme3(vec_new3(0,0, 1));
			e->COBJ.plimit->maxp = vec_new3(0, 0, 0);
			e->COBJ.plimit->minp = vec_new3(0, 0, 0);
			e->COBJ.plimit->r = 0;
			e->COBJ.plimit->t = -1;
			e->COBJ.plimit->normal = vec_norme3(vec_new3(0, 1, 1));
			e->COBJ.plimit->mat = create_matiere();
			e->COBJ.plimit->plimit_active = 0;
			chk = 1;
		}		
		++i;
	}
}

int				main(int argc, char **argv)
{
	t_rt	*e;

	e = (t_rt *)malloc(sizeof(t_rt));
	init_rt(e);
	if (argc > 2)
	{
		if (!parse_args(argv, argc, e))
			return (0);
		create_limits(e);
		ft_start_rt(e);
	}
	else
	{
		display_args();
	 	//ft_gtk_start(e, argc, argv);
	}
	return (0);
}
