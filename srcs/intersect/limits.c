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

static void		create_lnorme(t_rt *e, char **args)
{
	int i;

	i = SOBJ.nbr_limit;
	SOBJ.plimit[i].vector = vec_norme3(vec_new3(ft_atoi(args[2]),
	ft_atoi(args[3]), ft_atoi(args[4])));
	SOBJ.plimit[i].t = -1;
	SOBJ.plimit[i].normal = vec_norme3(vec_new3(ft_atoi(args[2]),
	ft_atoi(args[3]), ft_atoi(args[4])));
	SOBJ.plimit[i].plimit = NULL;
	SOBJ.nbr_limit = SOBJ.nbr_limit + 1;
}

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
		SOBJ.plimit[i].pos = vec_new3(ft_atoi(args[5]),
		ft_atoi(args[6]), ft_atoi(args[7]));
	else
		SOBJ.plimit[i].pos = SOBJ.pos;
	SOBJ.plimit[i].dir = vec_new3(0, 0, 0);
	SOBJ.plimit[i].k = ft_atoi(args[2]);
	SOBJ.plimit[i].mat = create_matiere();
	SOBJ.plimit[i].plimit_active = 0;
	SOBJ.plimit[i].nbr_limit = 0;
	if (SOBJ.plimit[i].r > 2)
		return ;
	create_lnorme(e, args);
}

float			limit_norme(float result, float obj_l,
	float obj_h, float plimit_dist)
{
	if (result > 0)
	{
		if (plimit_dist < obj_l && obj_l >= 0)
			return (obj_l);
		if (plimit_dist < obj_h && obj_h >= 0)
			return (obj_h);
		return (DIST_MAX);
	}
	else
	{
		if (plimit_dist > obj_l && obj_l >= 0)
			return (obj_l);
		if (plimit_dist > obj_h && obj_h >= 0)
			return (obj_h);
		return (DIST_MAX);
	}
}

float			limit_dist(t_obj obj, t_ray ray, float obj_l, float obj_h)
{
	float		plimit_dist;
	int			i;
	int			j;
	float		dist;

	i = -1;
	j = 0;
	plimit_dist = DIST_MAX;
	if (obj.plimit_active == 1 && obj_l != DIST_MAX)
	{
		while (++i < obj.nbr_limit - 1 && obj.plimit->type > 0)
		{
			dist = intersect_plane(ray, obj.plimit[i]);
			if (dist < plimit_dist)
			{
				plimit_dist = (dist < 0) ? plimit_dist : dist;
				j = i;
			}
		}
		//plimit_dist = intersect_plane(ray, obj.plimit[j]);
		return (limit_norme(vec_dot3(ray.dir, object_norm(obj.plimit[j],
		vec_add3(ray.pos, vec_scale3(ray.dir, plimit_dist)))),
		obj_l, obj_h, plimit_dist));
	}
	return (obj_l);
}
