/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.op.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccholin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/04 03:43:31 by ccholin           #+#    #+#             */
/*   Updated: 2017/08/04 03:43:35 by ccholin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

// int		ft_con_creator(t_vec3 v, t_vec3 v1, float angle, t_env *env)
// {
// 	obj.pos = vec_new3(v.x, v.y, v.z);
// 	obj.dir = vec_norme3(vec_new3(v1.x, v1.y, v1.z));
// 	obj.angle = ang / 180 * M_PI;
// 	return (ft_itemadator(env, item));
// }

// void		ft_set_normal_con(t_con *con, t_inter *inter)
// {
// 	inter->norm = vec_norme3(vec_sub3(ft_vec3_proj_vector(vec_norme3(
// 		vec_sub3(con->pos, inter->pos)), con->dir),
// 	vec_norme3(vec_sub3(con->pos, inter->pos))));
// }

float		intersect_cone2(t_ray ray, t_obj obj)
{
	t_calc	op;
	t_vec3	l;

	l = vec_sub3(ray.pos, obj.pos);
	op.a = vec_dot3(ray.dir, ray.dir) - (1.0 + tan(obj.angle)
		* tan(obj.angle)) * (vec_dot3(ray.dir, obj.dir)
		* vec_dot3(ray.dir, obj.dir));
	op.b = 2 * (vec_dot3(ray.dir, l) - (1.0 + tan(obj.angle)
		* tan(obj.angle)) * (vec_dot3(ray.dir, obj.dir)
		* vec_dot3(l, obj.dir)));
	op.c = vec_dot3(l, l) - (1.0 + tan(obj.angle) * tan(obj.angle))
	* (vec_dot3(l, obj.dir) * vec_dot3(l, obj.dir));
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
	// if ((op.t1 = (op.b * op.b - 4.0 * op.a * op.c)) <= 0)
	// 	return (-1);
	// op.t1 = ft_min(((-op.b + sqrt(op.t1)) / (2 * op.a)), ((-op.b - sqrt(op.t1)) / (2 * op.a)));
	// if (ft_check_t(inter, t, item) == 1 && f->impactmod)
	// {
	// 	ft_set_inter_pos(inter, s);
	// 	ft_set_normal_con(item->con, inter);
	// }
	return (DIST_MAX);
}