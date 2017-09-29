/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limits.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 09:02:55 by mhalit            #+#    #+#             */
/*   Updated: 2017/09/27 09:03:03 by mhalit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float       limit_dist(t_obj *obj, t_ray ray, float obj_lowdist, float obj_highdist)
{
    float   result;
    float	plimit_dist;
    if (obj->plimit_active == 1 && obj_lowdist != DIST_MAX)
	{
		plimit_dist = intersect_plane(ray, *(obj->plimit));
		result = vec_dot3(ray.dir, obj->plimit->vector);
		if (result > 0)
		{
			if (plimit_dist < obj_lowdist && obj_lowdist >= 0)
				return (obj_lowdist);
			if (plimit_dist < obj_highdist && obj_highdist >= 0)
				return (obj_highdist);
			return (DIST_MAX);
		}
		else
		{
			if (plimit_dist > obj_lowdist && obj_lowdist >= 0)
				return (obj_lowdist);
			if (plimit_dist > obj_highdist && obj_highdist >= 0)
				return (obj_highdist);
			return (DIST_MAX);
		}
	}
	return (obj_lowdist);
}
