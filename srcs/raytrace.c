/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocojeda- <ocojeda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 16:26:32 by tfaure            #+#    #+#             */
/*   Updated: 2017/09/19 18:24:12 by ocojeda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				obj_in_shadow(t_rt *e, t_vec3 poi, t_light light)
{
	t_ray	ray;
	float	dist;
	float	dist_to_light;
	t_vec3	n;

	n = vec_norme3(vec_sub3(light.ray.pos, poi));
	dist_to_light = get_length(n);
	ray = c_ray(vec_add3(poi, n), n);
	dist = get_min_dist(e, ray, 1);
	if (dist > 0 && dist < dist_to_light)
		return (1);
	else
		return (0);
}

t_color			get_color(t_rt *e, t_obj obj, t_vec3 poi)
{
	float		intensity;
	float		tmp;
	int			i;

	i = 0;
	intensity = 0;
	while (i < e->scene.nbr_light)
	{
		if (obj.type == SPHERE)
			tmp = intensity_sphere(poi, obj, e->CLIGHT);
		if (obj.type == PLANE)
			tmp = intensity_plane(e, poi, obj, e->CLIGHT);
		if (obj.type == CYLINDER)
		 	tmp = intensity_cylinder(e, poi, obj, e->CLIGHT);
		if (obj.type == CONE)
			tmp = intensity_cone(e, poi, obj, e->CLIGHT);
		if (obj_in_shadow(e, poi, e->CLIGHT))
			tmp -= 100 - AMBIENT_LIGHT;
		intensity += ((tmp > 2 * AMBIENT_LIGHT) ? tmp : 2 * AMBIENT_LIGHT);
		i++;
	}
	return ((i <= e->scene.nbr_light && intensity >= 0)
			? color_mult(obj.color, intensity) : (t_color){0, 0, 0, 0});
}

float			get_min_dist(t_rt *e, t_ray ray, int cangoneg)
{
	float		min_dist;
	float		dist;
	int			i;

	i = 0;
	dist = DIST_MAX;
	min_dist = DIST_MAX;
	while (i < e->scene.nbr_obj)
	{
		dist = (e->COBJ.type == SPHERE) ? intersect_sphere(ray, e->COBJ) : dist;
		dist = (e->COBJ.type == PLANE) ? intersect_plane(ray, e->COBJ) : dist;
		dist = (e->COBJ.type == CYLINDER) ? intersect_cylinder(ray, e->COBJ) : dist;
		dist = (e->COBJ.type == CONE) ? intersect_cone2(ray, e->COBJ) : dist;
		if (dist < min_dist)
		{
			min_dist = (cangoneg && dist < 0) ? min_dist : dist;
			e->scene.id = i;
		}
		i++;
	}
	return ((min_dist < DIST_MAX) ? min_dist : -1);
}

t_color			get_reflected_color(t_rt *e, t_ray ray, t_vec3 poi, t_color base_color)
{

	float		min_dist;
	float		dist;
	int			i;
	int a = 0;
	(void)base_color;

	//if(e->scene.id == PLANE)
	//{	
		ray.pos = poi;
		ray.dir = vec_sub3(poi, ray.dir);
	//}
	i = 0;
	//dist = DIST_MAX;
	//min_dist = DIST_MAX;
	while (i < e->scene.nbr_obj)
	{
		if (i != e->scene.id)
		{
			dist = (e->COBJ.type == SPHERE) ? intersect_sphere(ray, e->COBJ) : dist;
			dist = (e->COBJ.type == PLANE) ? intersect_plane(ray, e->COBJ) : dist;
			dist = (e->COBJ.type == CYLINDER) ? intersect_cylinder(ray, e->COBJ) : dist;
			dist = (e->COBJ.type == CONE) ? intersect_cone2(ray, e->COBJ) : dist;
			if (dist < min_dist)
			{
				min_dist = (dist < 0) ? min_dist : dist;
				a = i;
				//e->scene.id = i;
			}
		}
		i++;
	}
	t_vec3 point_of_impact = vec_add3(ray.pos, vec_scale3(ray.dir, min_dist));
	return get_color(e, e->scene.obj[a], point_of_impact);
	// je laisse base_color pour le utiliser apres avec une moyenne entre la couleur de base 
	// de lobjet reflectant et celui qui a etait trouve dans intersect
}

static t_color	get_pxl_color(t_rt *e, t_ray ray)
{
	float		min_dist;
	t_vec3		point_of_impact;
	t_color		color;
 
	color = (t_color){0, 0, 0, 0};
	e->scene.id = -1;
	if ((min_dist = get_min_dist(e, ray, 0)) == -1)
		return ((t_color){0, 0, 0, 0});
	point_of_impact = vec_add3(ray.pos, vec_scale3(ray.dir, min_dist));
	if (e->scene.id != -1)
	{
		if (e->scene.obj[e->scene.id].mat.reflex)
			return (get_reflected_color(e, ray, point_of_impact, get_color(e, e->scene.obj[e->scene.id], point_of_impact)));
		else
			color = get_color(e, e->scene.obj[e->scene.id], point_of_impact);
	}
	return (color);
}


t_color				raytrace(int x, int y, t_rt *e)
{
	t_color color;
	t_ray	ray;

	ray = ray_init(e, x, y);
	color = get_pxl_color(e, ray);
	 return (color);
}
