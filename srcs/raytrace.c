/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocojeda- <ocojeda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 23:07:54 by mhalit            #+#    #+#             */
/*   Updated: 2017/10/03 15:00:20 by ocojeda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color			raytrace(int x, int y, t_rt *e)
{
	t_color		color;
	t_ray		ray;

	ray = ray_init(e, x * RES / ALIASING, y * RES / ALIASING);
	color = get_pxl_color(e, ray);
	return (color);
}

t_color			get_color(t_rt *e, t_obj obj, t_vec3 poi)
{
	float		intensity;
	int			i;

	i = 0;
	intensity = 0;
	while (i < e->scene.nbr_light)
	{
		intensity += dazzling_light(e, e->CLIGHT,
		vec_norme3(vec_sub3(poi, CCAM.pos)));
		intensity += intensity_obj(e, poi, obj, e->CLIGHT);
		i++;
	}
	if (intensity != 0 && obj.mat.tex.is_init == 1)
		return (color_text(obj, poi, intensity));
	else if (intensity != 0)
		return (color_mult(obj.color, intensity));
	return ((t_color){0, 0, 0, 0});
}

float			get_min_dist(t_rt *e, t_ray ray)
{
	float		min_dist;
	float		dist;
	int			i;

	i = 0;
	dist = DIST_MAX;
	min_dist = DIST_MAX;
	while (i < e->scene.nbr_obj)
	{
		dist = intersect_obj(ray, e->COBJ);
		if (dist < min_dist)
		{
			min_dist = (dist < 0) ? min_dist : dist;
			e->scene.id = i;
		}
		i++;
	}
	return ((min_dist < DIST_MAX) ? min_dist : -1);
}

t_color			ret_reflected_pixel(t_rt *e, t_reflect ref, t_ray ray,
		float min_dist)
{
	t_color		temp_color;

	ref.color = get_color(e, e->scene.obj[e->scene.id], ref.poi);
	e->scene.id = ref.tmp_id;
	ref.color = ft_map_color(ref.color,
	get_reflected_color(e, ref.poi, ref.color, ref),
		e->scene.obj[ref.tmp_id].mat.reflex);
	e->scene.id = ref.tmp_id;
	if (e->scene.obj[e->scene.id].mat.refract)
	{
		ref.counter = NR_ITER;
		ref.ray = c_ray(ray.pos, ray.dir);
		ref.total_distance = 0;
		ref.poi = vec_add3(ray.pos, vec_scale3(ray.dir, min_dist));
		ref.color = get_color(e, e->scene.obj[e->scene.id], ref.poi);
		e->scene.id = ref.tmp_id;
		temp_color = copy_color(ref.color);
		return (ft_map_color(temp_color, get_refracted_color(e, ref.poi,
			ref.color, ref), 1 - e->scene.obj[e->scene.id].mat.refract));
	}
	return (ref.color);
}

static t_color	get_pxl_color(t_rt *e, t_ray ray)
{
	t_reflect	ref;

	e->scene.id = -1;
	if ((ref.min_dist = get_min_dist(e, ray)) == -1)
		return (skybox(e, ray));
	ref.tmp_id = e->scene.id;
	ref.poi = vec_add3(ray.pos, vec_scale3(ray.dir, ref.min_dist));
	ref.counter = NR_ITER;
	ref.ray = c_ray(ray.pos, ray.dir);
	if (e->scene.id != -1)
	{
		if (e->scene.obj[e->scene.id].mat.reflex)
			return (ret_reflected_pixel(e, ref, ray, ref.min_dist));
		if (e->scene.obj[e->scene.id].mat.refract)
		{
			ref.color = get_color(e, e->scene.obj[e->scene.id], ref.poi);
			e->scene.id = ref.tmp_id;
			return (get_refracted_color(e, ref.poi, ref.color, ref));
		}
		if (e->scene.obj[e->scene.id].mat.checker.l > 0)
			return (get_checker_col(e->scene.obj[e->scene.id].mat.checker,
					ref.poi));
			return (get_color(e, e->scene.obj[e->scene.id], ref.poi));
	}
	return (ref.color);
}
