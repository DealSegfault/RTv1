/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparigi <mparigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 18:11:22 by mparigi           #+#    #+#             */
/*   Updated: 2017/09/12 14:59:08 by mparigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static	void	key(t_rt *e)
{
	if (e->scene.selected == -1)
		move_cam(e, 10);
	else
		move_obj(e, 10);
	frame(e);
}

int     ft_close(void *param)
{
	param = NULL;
	exit(42);
	return (0);
}

int				keypress(int keycode, void *param)
{
	t_rt	*e;

	e = (t_rt *)param;
	if (keycode == KEY_ESC)
		exit(42);
	e->keys.key_w = (keycode == KEY_W) ? 1 : e->keys.key_w;
	e->keys.key_a = (keycode == KEY_A) ? 1 : e->keys.key_a;
	e->keys.key_s = (keycode == KEY_S) ? 1 : e->keys.key_s;
	e->keys.key_d = (keycode == KEY_D) ? 1 : e->keys.key_d;
	e->keys.key_up = (keycode == KEY_UP) ? 1 : e->keys.key_up;
	e->keys.key_left = (keycode == KEY_LEFT) ? 1 : e->keys.key_left;
	e->keys.key_down = (keycode == KEY_DOWN) ? 1 : e->keys.key_down;
	e->keys.key_right = (keycode == KEY_RIGHT) ? 1 : e->keys.key_right;
	e->keys.key_rotx_right = (keycode == KEY_E) ? 1 : e->keys.key_rotx_right;
	e->keys.key_rotx_left = (keycode == KEY_Q) ? 1 : e->keys.key_rotx_left;
	e->keys.key_roty_right = (keycode == KEY_C) ? 1 : e->keys.key_roty_right;
	e->keys.key_roty_left = (keycode == KEY_Z) ? 1 : e->keys.key_roty_left;
	e->keys.key_plus = (keycode == KEY_PLUS || keycode == 24) ? 1 : e->keys.key_plus;
	e->keys.key_minus = (keycode == KEY_MINUS || keycode == 27) ? 1 : e->keys.key_minus;
	key(e);
	return (keycode);
}

int				keyrelease(int keycode, void *param)
{
	t_rt	*e;

	e = (t_rt *)param;
	e->keys.key_w = (keycode == KEY_W) ? 0 : e->keys.key_w;
	e->keys.key_a = (keycode == KEY_A) ? 0 : e->keys.key_a;
	e->keys.key_s = (keycode == KEY_S) ? 0 : e->keys.key_s;
	e->keys.key_d = (keycode == KEY_D) ? 0 : e->keys.key_d;
	e->keys.key_up = (keycode == KEY_UP) ? 0 : e->keys.key_up;
	e->keys.key_left = (keycode == KEY_LEFT) ? 0 : e->keys.key_left;
	e->keys.key_down = (keycode == KEY_DOWN) ? 0 : e->keys.key_down;
	e->keys.key_right = (keycode == KEY_RIGHT) ? 0 : e->keys.key_right;
	e->keys.key_rotx_right = (keycode == KEY_E) ? 0 : e->keys.key_rotx_right;
	e->keys.key_rotx_left = (keycode == KEY_Q) ? 0 : e->keys.key_rotx_left;
	e->keys.key_roty_right = (keycode == KEY_C) ? 0 : e->keys.key_roty_right;
	e->keys.key_roty_left = (keycode == KEY_Z) ? 0 : e->keys.key_roty_left;
	e->keys.key_plus = (keycode == KEY_PLUS || keycode == 24) ? 0 : e->keys.key_plus;
	e->keys.key_minus = (keycode == KEY_MINUS || keycode == 27) ? 0 : e->keys.key_minus;
	return (keycode);
}
