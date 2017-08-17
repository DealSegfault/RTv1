/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocojeda- <ocojeda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 16:26:32 by tfaure            #+#    #+#             */
/*   Updated: 2017/08/17 16:29:57 by ocojeda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

int				obj_in_shadow(t_rt *e, t_vec3 poi, t_light light)
{
	t_ray	ray;
	float	dist;
	float	dist_to_light;

	dist_to_light = get_length(vec_sub3(light.ray.pos, poi));
	ray = c_ray(vec_add3(poi, vec_norme3(vec_sub3(light.ray.pos, poi))),
	vec_norme3(vec_sub3(light.ray.pos, poi)));
	dist = get_min_dist(e, ray, 1);
	if (dist > 0 && dist < dist_to_light)
		return (1);
	else
		return (0);
}

t_color			get_color(t_rt *e, t_obj obj, t_vec3 poi)
{
	float		intensity;
	int			i;

	i = 0;
	intensity = 0;
	while (i < e->scene.nbr_light)
	{
		if (obj.type == SPHERE)
			intensity += intensity_sphere(e, poi, obj, e->CLIGHT);
		if (obj.type == PLANE)
			intensity += intensity_plane(e, poi, obj, e->CLIGHT);
		if (obj.type == CYLINDER)
			intensity += intensity_cylinder(e, poi, obj, e->CLIGHT);
		if (obj.type == CONE)
			intensity += intensity_cone(e, poi, obj, e->CLIGHT);
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
		dist = (e->COBJ.type == CYLINDER) ?
			intersect_cylinder(ray, e->COBJ) : dist;
		dist = (e->COBJ.type == CONE) ? intersect_cone(ray, e->COBJ) : dist;
		if (dist < min_dist)
		{
			min_dist = (cangoneg && dist < 0) ? min_dist : dist;
			e->scene.id = i;
		}
		i++;
	}
	return ((min_dist < DIST_MAX) ? min_dist : -1);
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
		color = get_color(e, e->scene.obj[e->scene.id], point_of_impact);
	return (color);
}

t_vec3			get_vec(int x, int y, t_vec3 dir)
{
	t_vec3	ret;

	ret.x = WIDTH / 2 - x + dir.x;
	ret.y = HEIGHT / 2 - y + dir.y;
	ret.z = 250 + dir.z;
	return (ret);
}
/*
int				raytrace(int x, int y, t_rt *env)
{
	t_ray		ray;
	t_vec3		pov;
	t_color		color;

	pov = vec_new3((float)(x + env->scene.cam.ray.pos.x) / SS,
	(float)(y + env->scene.cam.ray.pos.y) / SS, 1);
	ray = c_ray(pov, vec_new3(0, 0, 1));
	color = get_pxl_color(env, ray);
	mlx_pixel(x, y, env, ret_colors(color));
	return (1);
}
*/
t_color				raytrace(int x, int y, t_rt *env)
{
	t_ray		ray;
	t_vec3		pov;
	t_color		color;

	color = c_color(0,0,0);
	pov = vec_new3((float)(x + env->scene.cam.ray.pos.x) / SS, 
		(float)(y + env->scene.cam.ray.pos.y) / SS, 1);
	ray = c_ray(pov, vec_new3(0, 0, 1));
	color = get_pxl_color(env, ray);
	return (color);
}