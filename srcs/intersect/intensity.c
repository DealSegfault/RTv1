/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intensity.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparigi <mparigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 21:36:08 by mparigi           #+#    #+#             */
/*   Updated: 2017/09/23 19:56:29 by mparigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define SIZE_LP 15 //The greater the value, the smaller the light point will be

#include "rt.h"

float			intensity_obj(t_rt *e, t_vec3 poi, t_obj obj, t_light light)
{
	float	intensity;
	t_vec3	norm;

	intensity = 0;
	light.ray.dir = vec_norme3(vec_sub3(light.ray.pos, poi));
	norm = object_norm(obj, poi);
	intensity += AMBIENT_LIGHT;
	if (!obj_in_shadow(e, poi, &light))
	{
		intensity += diff_intensity(obj, light.ray, norm);
		intensity += spec_intensity(obj, light.ray, norm);
	}
	return (intensity);
}

float		diff_intensity(t_obj obj, t_ray light, t_vec3 norm)
{
	float		intensity;

	if (obj.mat.diff == 0)
		return (0);
	intensity = vec_dot3(light.dir, norm) * obj.mat.diff;
	return ((intensity < 0) ? 0 : intensity);
}

float		spec_intensity(t_obj obj, t_ray light, t_vec3 norm)
{
	float		intensity;
	t_vec3		refl;

	refl = vec_sub3(light.dir, vec_scale3(norm, 2 * (vec_dot3(light.dir, norm))));
	if (obj.mat.spec == 0)
		return (0);
	intensity = vec_dot3(vec_scale3(light.dir, -1), refl);
	return ((intensity < 0) ? 0 : pow(intensity, SIZE_LP) * obj.mat.spec);
}