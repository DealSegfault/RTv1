/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 16:35:01 by mhalit            #+#    #+#             */
/*   Updated: 2017/09/04 16:35:09 by mhalit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		matrix_init(t_rt *e)
{
	t_mtrx4		transl;
	t_mtrx4		rotx;
	t_mtrx4		roty;
	t_mtrx4		rotz;

	transl = transl_matrx4((CPOS.x), (CPOS.y), CPOS.z);
	rotx = rotx_matrx4(e->scene.cam.rotx);
	roty = roty_matrx4(e->scene.cam.roty);
	rotz = rotz_matrx4(e->scene.cam.rotz);
	e->scene.cam.ctw = prod_matrx4(rotx, roty);
	e->scene.cam.ctw = prod_matrx4(rotz, e->scene.cam.ctw);
	e->scene.cam.ctw = prod_matrx4(transl, e->scene.cam.ctw);
}

t_ray		ray_init(t_rt *e, float x, float y)
{
    t_ray ray;
    t_vec3 new_pixel;
    float zoom;

    zoom = tan(e->scene.cam.fov / 2 * M_PI / 180);
	x = (2 * (((x * RES) + 0.5) / LARGEUR) - 1) * zoom * e->scene.cam.ratio_x;
	y = (1 - 2 * (((y * RES) + 0.5) / HAUTEUR)) * zoom * e->scene.cam.ratio_y;
	ray.pos = prod_vec3_matrx4(vec_new3(0, 0, 0), e->scene.cam.ctw);
	new_pixel = prod_vec3_matrx4(vec_new3(x, y, 1), e->scene.cam.ctw);
	ray.dir = vec_sub3(new_pixel, ray.pos);
	ray.dir = vec_norme3(ray.dir);
    return (ray);
}
