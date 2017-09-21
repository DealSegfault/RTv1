/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparigi <mparigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 20:08:17 by ocojeda-          #+#    #+#             */
/*   Updated: 2017/09/21 19:45:52 by mparigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3	plane_norm(t_obj obj)
{
	return (vec_norme3(vec_sub3(obj.pos, obj.vector)));
}

float			intensity_plane(t_rt *e, t_vec3 poi, t_obj plane, t_light light)
{
	t_vec3		dist_to_light;
	float		intensity;

	(void)e;
	(void)plane;
	dist_to_light = vec_sub3(light.ray.pos, poi);
	intensity = 0.5 * ft_map(get_length(dist_to_light),
		1200 * light.intensity, 470, 350);
	return (intensity);
}

float			intersect_plane(t_ray ray, t_obj plane)
{
	float		d;
	float		dist;
	t_vec3		vector_distance;

	d = vec_dot3(plane.vector, ray.dir);
	vector_distance = vec_sub3(plane.pos, ray.pos);
	dist = vec_dot3(vector_distance, plane.vector) / d;
	if (dist <= 0)
		return (DIST_MAX);
	else
		return (dist);
}
