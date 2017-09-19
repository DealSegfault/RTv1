/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparigi <mparigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 14:58:43 by mparigi           #+#    #+#             */
/*   Updated: 2017/09/12 14:59:32 by mparigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	move_cam(t_rt *e, int speed)
{
	t_ray	dir;
	t_vec3	rx;

	if (e->keys.key_w || e->keys.key_s || e->keys.key_a || e->keys.key_d)
	{
		dir = ray_init(e, LARGEUR / 2, HAUTEUR / 2);
		rx = vec_norme3(prod_vec3_matrx4(dir.dir, roty_matrx4(-90)));
		if (e->keys.key_w && !e->keys.key_s)
		{
			e->scene.cam.ray.pos.x += dir.dir.x * speed;
			e->scene.cam.ray.pos.y += dir.dir.y * speed;
			e->scene.cam.ray.pos.z += dir.dir.z * speed;
		}
		else if (e->keys.key_s && !e->keys.key_w)
		{
			e->scene.cam.ray.pos.x -= dir.dir.x * speed;
			e->scene.cam.ray.pos.y -= dir.dir.y * speed;
			e->scene.cam.ray.pos.z -= dir.dir.z * speed;
		}
		if (e->keys.key_a && !e->keys.key_d)
		{
			e->scene.cam.ray.pos.x += rx.x * speed;
			e->scene.cam.ray.pos.y += rx.y * speed;
			e->scene.cam.ray.pos.z += rx.z * speed;
		}
		else if (e->keys.key_d && !e->keys.key_a)
		{
			e->scene.cam.ray.pos.x -= rx.x * speed;
			e->scene.cam.ray.pos.y -= rx.y * speed;
			e->scene.cam.ray.pos.z -= rx.z * speed;
		}
	}
	e->scene.cam.ray.pos.y += (e->keys.key_plus && !e->keys.key_minus) ? 10 : 0;
	e->scene.cam.ray.pos.y -= (e->keys.key_minus && !e->keys.key_plus) ? 10 : 0;
	e->scene.cam.ray.dir.x += (e->keys.key_down && !e->keys.key_up) ? 5 : 0;
	e->scene.cam.ray.dir.x -= (e->keys.key_up && !e->keys.key_down) ? 5 : 0;
	e->scene.cam.ray.dir.y += (e->keys.key_right && !e->keys.key_left) ? 5 : 0;
	e->scene.cam.ray.dir.y -= (e->keys.key_left && !e->keys.key_right) ? 5 : 0;
}
void	move_obj(t_rt *e, int speed)
{
	t_ray	dir;
	t_vec3	rx;
	int i;

	i = e->scene.selected;
	if (e->keys.key_w || e->keys.key_s || e->keys.key_a || e->keys.key_d)
	{
		dir = ray_init(e, LARGEUR / 2, HAUTEUR / 2);
		rx = vec_norme3(prod_vec3_matrx4(dir.dir, roty_matrx4(-90)));
		if (e->keys.key_w && !e->keys.key_s)
		{
			e->COBJ.pos.x += dir.dir.x * speed;
			e->COBJ.pos.y += dir.dir.y * speed;
			e->COBJ.pos.z += dir.dir.z * speed;
		}
		else if (e->keys.key_s && !e->keys.key_w)
		{
			e->COBJ.pos.x -= dir.dir.x * speed;
			e->COBJ.pos.y -= dir.dir.y * speed;
			e->COBJ.pos.z -= dir.dir.z * speed;
		}
		if (e->keys.key_a && !e->keys.key_d)
		{
			e->COBJ.pos.x += rx.x * speed;
			e->COBJ.pos.y += rx.y * speed;
			e->COBJ.pos.z += rx.z * speed;
		}
		else if (e->keys.key_d && !e->keys.key_a)
		{
			e->COBJ.pos.x -= rx.x * speed;
			e->COBJ.pos.y -= rx.y * speed;
			e->COBJ.pos.z -= rx.z * speed;
		}
	}
	e->COBJ.pos.y += (e->keys.key_plus && !e->keys.key_minus) ? 10 : 0;
	e->COBJ.pos.y -= (e->keys.key_minus && !e->keys.key_plus) ? 10 : 0;
}


int		select_obj(int button, int x, int y, t_rt *e)
{
	t_ray	ray;

	if (button == 1)
	{
		ray = ray_init(e, x, y);
		get_min_dist(e, ray, 1);
		e->scene.selected = e->scene.id;
	}
	e->scene.selected = (button == 2) ? -1 : e->scene.selected;
	e->scene.cam.fov -= (button == SCROLLUP) ? 2 : 0;
	e->scene.cam.fov += (button == SCROLLDOWN) ? 2 : 0;
	frame(e);
	return (button);
}
