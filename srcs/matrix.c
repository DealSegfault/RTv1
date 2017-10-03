/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparigi <mparigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 18:30:48 by mhalit            #+#    #+#             */
/*   Updated: 2017/10/02 00:22:59 by mparigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float		p(float x)
{
	return (pow(x, 2));
}

void		matrix_init(t_rt *e)
{
	t_mtrx4		transl;

	transl = transl_matrx4(CCAM.pos.x, CCAM.pos.y, CCAM.pos.z);
	CCAM.ctw = id_matrx4();
	CCAM.ctw = prod_matrx4(CCAM.ctw, rotz_matrx4(CCAM.rot.z));
	CCAM.ctw = prod_matrx4(CCAM.ctw, roty_matrx4(CCAM.rot.y));
	CCAM.ctw = prod_matrx4(CCAM.ctw, rotx_matrx4(CCAM.rot.x));
	CCAM.ctw = (!CCAM.is_circular) ? prod_matrx4(transl, CCAM.ctw) :
				prod_matrx4(CCAM.ctw, transl);
}

t_ray		ray_init(t_rt *e, int x, int y)
{
	t_ray	ray;
	t_vec3	px;
	float	fov;

	fov = tan(CCAM.fov / 2 * DEG2RAD);
	px = vec_new3((2 * ((x + 0.5) / LARGEUR) - 1) * fov * CCAM.ratio_x,
		(1 - 2 * ((y + 0.5) / HAUTEUR)) * fov * CCAM.ratio_y, 1);
	ray.pos = prod_vec3_matrx4(vec_new3(0, 0, 0), CCAM.ctw);
	px = prod_vec3_matrx4(px, CCAM.ctw);
	ray.dir = vec_norme3(vec_sub3(px, ray.pos));
	e->scene.max_iter = 3;
	return (ray);
}
