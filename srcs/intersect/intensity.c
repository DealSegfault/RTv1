/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intensity.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparigi <mparigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 21:36:08 by mparigi           #+#    #+#             */
/*   Updated: 2017/10/03 18:43:09 by mparigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float		dazzling_light(t_rt *e, t_light light, t_vec3 cam_dir)
{
	float	intensity;
	float	dot;
	t_vec3	refl;
	float	transp;

	light.ray.dir = vec_sub3(light.ray.pos, CCAM.pos);
	if (!(transp = obj_isnt_in_shadow(e, CCAM.pos, &light)))
		return (0);
	light.ray.dir = vec_norme3(light.ray.dir);
	if ((dot = vec_dot3(light.ray.dir, cam_dir)) < EPSILON)
		return (0);
	refl = vec_sub3(light.ray.dir, vec_scale3(cam_dir, 2 * dot));
	intensity = vec_dot3(vec_scale3(light.ray.dir, -1), refl);
	return ((intensity < 0) ? 0 : pow(intensity, 500) * 2 * transp);
}

float		intensity_obj(t_rt *e, t_vec3 poi, t_obj obj, t_light light)
{
	float	intensity;
	t_vec3	norm;
	float	transp;
	float	dot;

	intensity = 0;
	transp = 0;
	light.ray.dir = vec_norme3(vec_sub3(light.ray.pos, poi));
	norm = color_norm(obj, poi, vec_sub3(CCAM.pos, poi));
	if ((dot = vec_dot3(light.ray.dir, norm)) > 0
		&& (transp = obj_isnt_in_shadow(e, poi, &light)))
	{
		intensity += diff_intensity(obj, dot);
		intensity += spec_intensity(obj, light.ray, norm, dot);
	}
	return (intensity * transp + AMBIENT_LIGHT);
}

float		diff_intensity(t_obj obj, float dot)
{
	float	intensity;

	if (obj.mat.diff == 0)
		return (0);
	intensity = dot * obj.mat.diff;
	return ((intensity < 0) ? 0 : intensity);
}

float		spec_intensity(t_obj obj, t_ray light, t_vec3 norm, float dot)
{
	float	intensity;
	t_vec3	refl;

	if (obj.mat.spec == 0)
		return (0);
	refl = vec_sub3(light.dir, vec_scale3(norm, 2 * dot));
	intensity = vec_dot3(vec_scale3(light.dir, -1), refl);
	return ((intensity < 0) ? 0 : pow(intensity, SIZE_LP) * obj.mat.spec);
}
