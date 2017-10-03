/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 17:38:17 by mhalit            #+#    #+#             */
/*   Updated: 2017/09/30 17:38:19 by mhalit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3		cylinder_norm(t_obj cyl, t_vec3 poi)
{
	t_vec3		normal;
	t_vec3		tmp;
	t_vec3		project;
	float		dot;

	tmp = vec_sub3(poi, cyl.pos);
	dot = vec_dot3(tmp, cyl.vector);
	project = vec_scale3(cyl.vector, dot);
	normal = vec_sub3(tmp, project);
	if (cyl.mat.sin == 1)
	{
		normal.x = normal.x;
		normal.y = sin(normal.y) * 20;
		normal.z = normal.z;
	}
	return (vec_norme3(normal));
}

float		vec_dot2(t_vec3 u, t_vec3 v, t_vec3 axis)
{
	if (axis.x)
		return (u.y * v.y + u.z * v.z);
	else if (axis.y)
		return (u.x * v.x + u.z * v.z);
	return (u.x * v.x + u.y * v.y);
}

float		intersect_cylinder(t_ray ray, t_obj obj)
{
	t_calc	op;
	float	dotdv;
	float	dotxv;
	t_vec3	x;

	x = vec_sub3(ray.pos, obj.pos);
	dotdv = vec_dot3(ray.dir, obj.vector);
	dotxv = vec_dot3(x, obj.vector);
	op.a = vec_dot3(ray.dir, ray.dir) - p(dotdv);
	op.b = 2 * (vec_dot3(ray.dir, x) - dotdv * dotxv);
	op.c = vec_dot3(x, x) - p(dotxv) - p(obj.r);
	op.eq = get_res_of_quadratic2(&op);
	if (op.eq == op.t0)
		return (limit_dist(obj, ray, op.eq, op.t1));
	else
		return (limit_dist(obj, ray, op.eq, op.t0));
}
