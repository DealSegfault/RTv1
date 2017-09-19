/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfaure <tfaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 20:08:17 by ocojeda-          #+#    #+#             */
/*   Updated: 2017/08/21 13:04:49 by tfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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

	d = vec_dot3(plane.normal, ray.dir);
	if (fabs(d) > EPSILON)
	{
		vector_distance = vec_sub3(plane.pos, ray.pos);
		dist = vec_dot3(vector_distance, plane.normal) / d;
		return (dist);
	}
	return (DIST_MAX);
}
