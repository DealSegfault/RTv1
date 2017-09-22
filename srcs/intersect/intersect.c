/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparigi <mparigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 05:07:11 by mparigi           #+#    #+#             */
/*   Updated: 2017/09/22 05:14:20 by mparigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float			intersect_obj(t_ray ray, t_obj obj)
{
	if (obj.type == CYLINDER)
		return (intersect_cylinder(ray, obj));
	else if (obj.type == SPHERE)
		return (intersect_sphere(ray, obj));
	else if (obj.type == PLANE)
		return (intersect_plane(ray, obj));
	else if (obj.type == CONE)
		return (intersect_cone(ray, obj));
	return (DIST_MAX);
}

t_vec3			object_norm(t_obj obj, t_vec3 poi)
{
	if (obj.type == CYLINDER)
		return (vec_norme3(cylinder_norm(obj, poi)));
	if (obj.type == SPHERE)
		return (vec_norme3(sphere_norm(obj, poi)));
	if (obj.type == PLANE)
		return (vec_norme3(plane_norm(obj)));
	if (obj.type == CONE)
		return (cone_norm(obj, poi));
	return (vec_new3(0, 0, 0));
}

int				obj_in_shadow(t_rt *e, t_vec3 poi, t_light *light)
{
	t_ray	ray;
	float	dist;
	float	dist_to_light;

	light->ray.dir = vec_sub3(light->ray.pos, poi);
	dist_to_light = get_length(light->ray.dir);
	light->ray.dir = vec_norme3(light->ray.dir);
	ray = c_ray(vec_add3(poi, light->ray.dir), light->ray.dir);
	dist = get_min_dist(e, ray);
	if (dist > 0 && dist < dist_to_light)
		return (1);
	else
		return (0);
}

float	get_res_of_quadratic(float a, float b, float c)
{
	float	t0;
	float	t1;
	float	delta;
	float	sqr;

	if (a == 0)
		return (-c / b);
	delta = p(b) - 4 * a * c;
	if (delta < 0)
		return (DIST_MAX);
	if (delta == 0)
		return (-b / (2 * a));
	sqr = sqrt(delta);
	t0 = ((-b + sqr) / (2 * a));
	t1 = ((-b - sqr) / (2 * a));
	if ((t0 < t1 || t1 < EPSILON) && t0 > EPSILON)
		return (t0);
	else if ((t1 < t0 || t0 < EPSILON) && t1 > EPSILON)
		return (t1);
	return (DIST_MAX);
}
