/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldenblyd <ldenblyd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 15:04:18 by mhalit            #+#    #+#             */
/*   Updated: 2017/10/04 17:02:38 by ldenblyd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3			sphere_norm(t_obj obj, t_vec3 poi)
{
	t_vec3	norme;

	norme = vec_norme3(vec_sub3(poi, obj.pos));
	return (norme);
}

float			intersect_sphere(t_ray ray, t_obj *sphere)
{
	t_vec3		x;
	t_calc		op;

	ray.dir = vec_norme3(ray.dir);
	x = vec_sub3(ray.pos, sphere->pos);
	op.a = vec_dot3(ray.dir, ray.dir);
	op.b = 2 * vec_dot3(ray.dir, x);
	op.c = vec_dot3(x, x) - (sphere->r * sphere->r);
	op.eq = get_res_of_quadratic(&op, sphere);
	if (op.eq == op.t0)
		return (limit_dist(*sphere, ray, op.eq, op.t1));
	else
		return (limit_dist(*sphere, ray, op.eq, op.t0));
}
