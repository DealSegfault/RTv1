/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflexion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocojeda- <ocojeda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/23 07:03:06 by mhalit            #+#    #+#             */
/*   Updated: 2017/09/29 09:31:06 by ocojeda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
/*
* ref ref is for reflectedorfreacted
*/
t_color 		add_refref_colors(t_rt *e, t_ray ray, float min_dist, int counter, int a, t_color base_color)
{
	t_vec3		point_of_impact;
	t_color		final_color;
	float		taux_temp;

	taux_temp = e->scene.obj[e->scene.id].mat.reflex;
	point_of_impact = vec_add3(ray.pos, vec_scale3(ray.dir, min_dist));
	final_color = get_color(e, e->scene.obj[a], point_of_impact);
	base_color = ft_map_color(base_color, final_color, taux_temp);
	e->scene.id = a;
	if (e->scene.obj[a].mat.refract)
		return (get_refracted_color(e, point_of_impact, base_color, counter, ray));
	else if (e->scene.obj[a].mat.reflex)
		return (get_reflected_color(e, point_of_impact, base_color, counter, ray));
	return base_color;
}

t_color			get_reflected_color(t_rt *e, t_vec3 poi, t_color base_color, int counter, t_ray rayon)
{

	float		min_dist;
	int         a;
	t_ray 		ray;
	(void) 		rayon;
	float		taux_temp;

	if(counter == 0)
		return base_color;
	counter--;
	ray.dir = object_norm(e->scene.obj[e->scene.id], poi);
	ray.pos = poi;
	if(e->scene.obj[e->scene.id].type == SPHERE)
	{
		ray.pos = vec_norme3(e->scene.obj[e->scene.id].pos);
		ray.dir = vec_add3(object_norm(e->scene.obj[e->scene.id], poi), ray.pos);
	}
	taux_temp = e->scene.obj[e->scene.id].mat.reflex;
	min_dist = find_min_dist_for_refref(e, &a, ray);
	if(min_dist < DIST_MAX)
		return add_refref_colors(e, ray, min_dist, counter, a, base_color);
	return ft_map_color(base_color, skybox(e, ray), taux_temp);
}