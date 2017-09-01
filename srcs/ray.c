/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeldame <bbeldame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 14:55:55 by tfaure            #+#    #+#             */
/*   Updated: 2017/08/18 00:53:04 by rlecart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float	get_length(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_ray		c_ray(t_vec3 i, t_vec3 j)
{
	t_ray	ray;
	
	ray.pos = vec_new3(i.x, i.y, i.z);
	ray.dir = vec_norme3(vec_new3(j.x, j.y, j.z));
	return (ray);
}

t_vec3			get_vec(int x, int y, t_vec3 dir, t_rt *e)
{
	// t_vec3	ret;

	if (x && y)
		x = 0;

	// ret.x = LARGEUR / 2 - x + dir.x;
	// ret.y = HAUTEUR / 2 - y + dir.y;
	// ret.z = 250 + dir.z;

	t_ray	ray;
	float	coeff;
	float 	w;
	float 	h;

	coeff = (LARGEUR < HAUTEUR ? LARGEUR : HAUTEUR);
	w = LARGEUR / coeff;
	h = HAUTEUR / coeff;
	
	// ray.pos = vec_new3((float)(x + CPOS.x) * RES, (float)(y + CPOS.y) * RES, CPOS.z);
	ray.dir = vec_norme3(dir);
	ray.dir = vec_add3(ray.dir, vec_sub3(vec_scale3((t_vec3){ 1, 0, 0, 0}, w / LARGEUR * dir.x), vec_scale3((t_vec3){0, 1, 0, 0}, h / HAUTEUR * dir.y)));
	ray.dir = vec_norme3(ray.dir);

	return (ray.dir);
}

