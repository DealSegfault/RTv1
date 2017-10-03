/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparigi <mparigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 14:58:43 by mparigi           #+#    #+#             */
/*   Updated: 2017/10/02 00:14:38 by mparigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			filters_press(int keycode, t_rt *e)
{
	e->scene.filters = (keycode == KEY_1) ? 0 : e->scene.filters;
	e->scene.filters = (keycode == KEY_2) ? 1 : e->scene.filters;
	e->scene.filters = (keycode == KEY_3) ? 2 : e->scene.filters;
	e->scene.filters = (keycode == KEY_4) ? 3 : e->scene.filters;
	e->scene.filters = (keycode == KEY_5) ? 4 : e->scene.filters;
	e->scene.filters = (keycode == KEY_6) ? 5 : e->scene.filters;
	e->scene.filters = (keycode == KEY_7) ? 6 : e->scene.filters;
}

void			onepress(int keycode, t_rt *e)
{
	filters_press(keycode, e);
	if (e->scene.selected != -1)
	{
		if ((keycode == 81) || (keycode == 75))
			e->scene.obj[e->scene.selected].r += (keycode == 81) ? 10 : -10;
		if (e->scene.obj[e->scene.selected].r == 0)
			e->scene.obj[e->scene.selected].r = 5;
	}
	if (keycode == LSHIFT)
		AMBIENT_LIGHT += ((int)AMBIENT_LIGHT == 1) ? -1 : 0.05;
	RES += (keycode == PAGE_UP && RES < 200) ? 1 : 0;
	RES -= (keycode == PAGE_DOWN && RES > 1) ? 1 : 0;
	if (RES < 1)
		RES = 1;
	if (keycode == PAGE_UP || keycode == PAGE_DOWN)
	{
		RES_BUFF = RES;
		frame(e);
	}
	if (keycode == KEY_C)
		cam_mode(e);
	if (keycode == 50)
		exportimg(e);
	gtk_hook(keycode, e);
}

void			move(t_rt *e, t_vec3 *vec, int speed)
{
	t_ray	dir;
	t_vec3	rx;

	dir = ray_init(e, LARGEUR / 2, HAUTEUR / 2);
	rx = vec_norme3(prod_vec3_matrx4(
		vec_new3(dir.dir.x, 0, dir.dir.z), roty_matrx4(-90)));
	if ((e->keys.key_w && !e->keys.key_s) || (e->keys.key_s && !e->keys.key_w))
	{
		vec->x += (e->keys.key_w) ? dir.dir.x * speed : dir.dir.x * -speed;
		vec->y += (e->keys.key_w) ? dir.dir.y * speed : dir.dir.y * -speed;
		vec->z += (e->keys.key_w) ? dir.dir.z * speed : dir.dir.z * -speed;
	}
	if ((e->keys.key_a && !e->keys.key_d) || (e->keys.key_d && !e->keys.key_a))
	{
		vec->x += (e->keys.key_a) ? rx.x * speed : rx.x * -speed;
		vec->y += (e->keys.key_a) ? rx.y * speed : rx.y * -speed;
		vec->z += (e->keys.key_a) ? rx.z * speed : rx.z * -speed;
	}
	vec->y += (e->keys.key_plus && !e->keys.key_minus) ? 10 : 0;
	vec->y -= (e->keys.key_minus && !e->keys.key_plus) ? 10 : 0;
}

void			move_cam(t_rt *e, int speed)
{
	CCAM.rot.x += (e->keys.key_down && !e->keys.key_up) ? 1 : 0;
	CCAM.rot.x -= (e->keys.key_up && !e->keys.key_down) ? 1 : 0;
	CCAM.rot.y += (e->keys.key_right && !e->keys.key_left) ? 1 : 0;
	CCAM.rot.y -= (e->keys.key_left && !e->keys.key_right) ? 1 : 0;
	CCAM.rot.z += (e->keys.key_q && !e->keys.key_e) ? 1 : 0;
	CCAM.rot.z -= (e->keys.key_e && !e->keys.key_q) ? 1 : 0;
	CCAM.rot.x = (CCAM.rot.x > 360) ? 0 : CCAM.rot.x;
	CCAM.rot.x = (CCAM.rot.x < 0) ? 360 : CCAM.rot.x;
	CCAM.rot.y = (CCAM.rot.y > 360) ? 0 : CCAM.rot.y;
	CCAM.rot.y = (CCAM.rot.y < 0) ? 360 : CCAM.rot.y;
	CCAM.rot.z = (CCAM.rot.z > 360) ? 0 : CCAM.rot.z;
	CCAM.rot.z = (CCAM.rot.z < 0) ? 360 : CCAM.rot.z;
	if (!CCAM.is_circular && (e->keys.key_w || e->keys.key_s
	|| e->keys.key_a || e->keys.key_d || e->keys.key_plus || e->keys.key_minus))
		move(e, &CCAM.pos, speed);
	if (CCAM.is_circular && (e->keys.key_w || e->keys.key_s
	|| e->keys.key_a || e->keys.key_d || e->keys.key_plus || e->keys.key_minus))
	{
		CCAM.pos.x += (e->keys.key_d && !e->keys.key_a) ? 10 : 0;
		CCAM.pos.x -= (e->keys.key_a && !e->keys.key_d) ? 10 : 0;
		CCAM.pos.z += (e->keys.key_w && !e->keys.key_s) ? 10 : 0;
		CCAM.pos.z -= (e->keys.key_s && !e->keys.key_w) ? 10 : 0;
		CCAM.pos.y += (e->keys.key_plus && !e->keys.key_minus) ? 10 : 0;
		CCAM.pos.y -= (e->keys.key_minus && !e->keys.key_plus) ? 10 : 0;
	}
}

void			move_obj(t_rt *e, int speed)
{
	int i;

	i = 0;
	if (e->keys.key_w || e->keys.key_s || e->keys.key_a ||
	e->keys.key_d || e->keys.key_minus || e->keys.key_plus
	|| e->keys.key_plus || e->keys.key_minus)
	{
		while (i < e->scene.nbr_obj)
		{
			if (e->scene.obj[i].id == e->scene.obj[e->scene.selected].id)
			{
				move(e, &e->scene.obj[i].pos, speed);
				if (ISLIMIT == 1)
					move(e, &e->scene.obj[i].plimit->pos, speed);
			}
			i++;
		}
	}
}
