/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparigi <mparigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 11:58:42 by mhalit            #+#    #+#             */
/*   Updated: 2017/10/02 00:22:29 by mparigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			exportimg(t_rt *e)
{
	t_file		export;
	int			pos;

	ft_putendl("Exporting image ...");
	if (!(export.fdp = open("first.ppm", O_WRONLY | O_CREAT, 00755)))
		return ;
	ft_putstr_fd("P6 ", export.fdp);
	ft_putnbr_fd(LARGEUR, export.fdp);
	ft_putstr_fd(" ", export.fdp);
	ft_putnbr_fd(HAUTEUR, export.fdp);
	ft_putstr_fd(" 255\n", export.fdp);
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
	ft_putendl("Image exported !");
}

void			new_rt(void)
{
	t_rt	*e;

	e = (t_rt *)malloc(sizeof(t_rt));
	init_rt(e);
	ft_gtk_start_launcher(e);
}

void			show_settings(t_rt *e)
{
	mlx_destroy_window(INIT, WIN);
	ft_gtk_start_settings(e);
}

void			cam_mode(t_rt *e)
{
	t_vec3	tmp;

	CCAM.is_circular = (CCAM.is_circular) ? 0 : 1;
	tmp = CCAM.pos;
	CCAM.pos = CCAM.tmp_pos;
	CCAM.tmp_pos = tmp;
	tmp = CCAM.rot;
	CCAM.rot = CCAM.tmp_rot;
	CCAM.tmp_rot = tmp;
}

void			gtk_hook(int keycode, t_rt *e)
{
	if (keycode == KEY_N || keycode == KEY_O)
		key_init(e);
	if (keycode == KEY_N)
		new_rt();
	else if (keycode == KEY_O)
		show_settings(e);
}
