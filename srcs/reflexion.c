/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflexion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocojeda- <ocojeda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/23 07:03:06 by mhalit            #+#    #+#             */
/*   Updated: 2017/10/03 15:01:27 by ocojeda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float			find_min_dist_for_refref(t_rt *e, int *a, t_ray ray)
{
	float		min_dist;
	float		dist;
	int			i;

	i = 0;
	dist = 0;
	min_dist = DIST_MAX;
	while (i < e->scene.nbr_obj)
	{
		if (i != e->scene.id)
		{
			dist = intersect_obj(ray, e->COBJ);
			if (dist < min_dist)
			{
				min_dist = dist;
				*a = i;
			}
		}
		i++;
	}
	return (min_dist);
}

t_color			recursive_refref(t_rt *e, t_color base_color, t_reflect ref)
{
	t_color color1;

	if (e->scene.obj[ref.a].mat.refract)
	{
		if (e->scene.obj[ref.a].mat.refract == 1)
			return (get_refracted_color(e, ref.poi, base_color, ref));
		ref.dist_rate *= e->scene.obj[ref.a].mat.refract;
		color1 = get_refracted_color(e, ref.poi, base_color, ref);
		return (ft_map_color(base_color, color1, ref.dist_rate));
	}
	else
	{
		if (e->scene.obj[ref.a].mat.reflex == 1)
			return (get_reflected_color(e, ref.poi, base_color, ref));
		ref.dist_rate *= e->scene.obj[ref.a].mat.reflex;
		color1 = get_reflected_color(e, ref.poi, base_color, ref);
		return (ft_map_color(base_color, color1, ref.dist_rate));
	}
}

t_color			add_refref_colors(t_rt *e, int a, t_color base_color,
t_reflect ref)
{
	t_vec3		point_of_impact;
	t_color		final_color;
	float		temp_rate;
	float		distance_rate;

	distance_rate = ft_map(ref.min_dist, ref.total_distance, 0, 1);
	temp_rate = e->scene.obj[e->scene.id].mat.reflex;
	point_of_impact = vec_add3(ref.ray.pos, vec_scale3(ref.ray.dir,
	ref.min_dist));
	final_color = get_color(e, e->scene.obj[a], point_of_impact);
	base_color = ft_map_color(base_color, final_color, temp_rate);
	e->scene.id = a;
	ref.a = a;
	ref.ray = c_ray(point_of_impact, ref.new_ray.dir);
	ref.poi = vec_scale3(point_of_impact, 1);
	ref.dist_rate = distance_rate;
	if (e->scene.obj[a].mat.refract || e->scene.obj[a].mat.reflex)
		return (recursive_refref(e, base_color, ref));
	return (base_color);
}

t_color			get_reflected_color(t_rt *e, t_vec3 poi,
t_color base_color, t_reflect ref)
{
	int			a;
	float		temp_rate;

	if (ref.counter == 0)
		return (base_color);
	ref.counter--;
	ref.new_ray = c_ray(poi, object_norm(e->scene.obj[e->scene.id], poi));
	temp_rate = e->scene.obj[e->scene.id].mat.reflex;
	ref.min_dist = find_min_dist_for_refref(e, &a, ref.new_ray);
	ref.total_distance = ref.total_distance + ref.min_dist;
	if (ref.min_dist < DIST_MAX)
		return (add_refref_colors(e, a, base_color, ref));
	return (ft_map_color(base_color, skybox(e, ref.new_ray), temp_rate));
}
