/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocojeda- <ocojeda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 20:18:47 by ocojeda-          #+#    #+#             */
/*   Updated: 2017/08/17 21:21:50 by rlecart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float	intensity_cone(t_rt *e, t_vec3 poi, t_obj cone, t_light light)
{
	t_vec3	dist_to_light;
	float	intensity;

	(void)e;
	(void)cone;
	dist_to_light = vec_sub3(light.ray.pos, poi);
	intensity = 0.5 * ft_map(get_length(dist_to_light),
			2000 * light.intensity, 500, 200);
	return (intensity > 0) ? intensity : 0;
}

float			intersect_cone(t_ray ray, t_obj cone)
{
	t_calc		op;
	t_vec3		x;

	x = vec_sub3(cone.pos, ray.pos);
	op.a = vec_dot3(ray.dir, ray.dir) -
		vec_dot3(ray.dir, cone.normal);
	op.c = vec_dot3(x, x) - pow(vec_dot3(x, cone.normal), 2) -
		pow(cone.r, 2);
	op.b = 2 * (vec_dot3(ray.dir, x) -
			(vec_dot3(ray.dir, cone.normal) * vec_dot3(x, cone.normal)));
	op.disc = op.b * op.b - 4 * op.a * op.c;
	if (op.disc >= 0)
	{
		op.disc = sqrt(op.disc);
		op.t0 = (-op.b - op.disc) / (2 * op.a);
		op.t1 = (-op.b + op.disc) / (2 * op.a);
		if (op.t0 > op.t1)
			return (op.t1);
		else
			return (op.t0);
	}
	return (DIST_MAX);
}
