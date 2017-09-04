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

void		init_rt(t_rt *e)
{
	e->mlx.init = mlx_init();
	e->file.larg = 1024;
	e->file.haut = 768;
	e->file.reso = 2;
	e->scene.nbr_obj = 0;
	e->scene.nbr_light = 0;
	e->scene.nbr_tot = 0;
	e->scene.obj = (t_obj *)malloc(sizeof(t_obj) * MAXOBJ);
	e->scene.lights = (t_light *)malloc(sizeof(t_light) * MAXLIGHT);
	e->scene.supersampling = 1;
	e->scene.filters = 0;
}

int			main(int argc, char **argv)
{
	t_rt	*e;

	e = (t_rt *)malloc(sizeof(t_rt));
	if (argc > 2)
	{
		init_rt(e);
		if (!parse_args(argv, argc, e))
			return (0);
		if (!HAUTEUR || !LARGEUR)
			return (0);
		e->mlx.window = mlx_new_window(e->mlx.init, e->file.larg, e->file.haut, "RT Again");
		IMG = mlx_new_image(INIT, LARGEUR, HAUTEUR);
		e->mlx.data = mlx_get_data_addr(IMG, &e->mlx.bpp, &e->mlx.size_l,
		&e->mlx.endian);
		frame(e);
		mlx_key_hook(e->mlx.window, key_hook, e);
		//mlx_mouse_hook(WIN, mouse_hook, e);
		mlx_loop(INIT);
	}
	else
		display_args();
	return (0);
}
