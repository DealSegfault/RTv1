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

void			create_limits(t_rt *e, char **args, int tot)
{
	int i;

	SOBJ.plimit_active = 1;
	i = SOBJ.nbr_limit;
	SOBJ.plimit_type = 0;
	SOBJ.plimit_active = 1;
	SOBJ.plimit[i].is_init = -1;
	SOBJ.plimit[i].type = ft_atoi(args[1]);
	SOBJ.plimit[i].r = ft_atoi(args[2]);
	SOBJ.plimit[i].color = SOBJ.color;
	if (tot == 8)
		SOBJ.plimit[i].pos = vec_new3(ft_atoi(args[5]),ft_atoi(args[6]), ft_atoi(args[7]));
	else
		SOBJ.plimit[i].pos = SOBJ.pos;
	SOBJ.plimit[i].dir = vec_new3(0, 0, 0);
	SOBJ.plimit[i].k = ft_atoi(args[2]);
	SOBJ.plimit[i].mat = create_matiere();
	SOBJ.plimit[i].plimit_active = 0;
	SOBJ.plimit[i].nbr_limit = 0;
	if (SOBJ.plimit[i].r > 2)
		return ;
	SOBJ.plimit[i].vector = vec_norme3(vec_new3(ft_atoi(args[2]),ft_atoi(args[3]), ft_atoi(args[4])));
	SOBJ.plimit[i].maxp = vec_new3(0, 0, 0);
	SOBJ.plimit[i].minp = vec_new3(0, 0, 0);
	SOBJ.plimit[i].t = -1;
	SOBJ.plimit[i].normal = vec_norme3(vec_new3(ft_atoi(args[2]),ft_atoi(args[3]), ft_atoi(args[4])));
	SOBJ.plimit[i].plimit = NULL;
	SOBJ.nbr_limit = SOBJ.nbr_limit + 1;
}

float       limit_dist(t_obj obj, t_ray ray, float obj_lowdist, float obj_highdist)
{
    float   result;
    float	plimit_dist;

	plimit_dist = DIST_MAX;
    if (obj.plimit_active == 1 && obj_lowdist != DIST_MAX)
	{
		float 	dist;
		int i = 0;
		int j = 0;
		while (i < obj.nbr_limit && obj.type > 0)
		{
			dist = intersect_obj(ray, obj.plimit[i]);
			if (dist < plimit_dist)
			{
				plimit_dist = (dist < 0) ? plimit_dist : dist;
				j = i;
			}
			i++;
		}
		plimit_dist = intersect_plane(ray, obj.plimit[j]);
		t_vec3 point_of_impact = vec_add3(ray.pos, vec_scale3(ray.dir, plimit_dist));
		result = vec_dot3(ray.dir, object_norm(obj.plimit[j], point_of_impact));
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
