/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copyrt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparigi <mparigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 23:14:17 by mparigi           #+#    #+#             */
/*   Updated: 2017/09/27 13:13:13 by mhalit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_light				copy_light(t_light light)
{
	t_light			copy;

	copy.is_init = light.is_init;
	copy.ray = light.ray;
	copy.color = light.color;
	copy.intensity = light.intensity;
	return (copy);
}

t_obj				*copy_limit(t_obj lim)
{
	int				i;
	t_obj			*copy;

	i = -1;
	if (!(copy = malloc(sizeof(t_obj) * MAXLIM + 1)))
		return (NULL);
	while (++i < lim.nbr_limit)
		copy[i] = lim.plimit[i];
	return (copy);
}

t_obj				copy_objs(t_obj obj)
{
	t_obj			copy;

	copy.is_init = obj.is_init;
	copy.type = obj.type;
	copy.color = obj.color;
	copy.pos = obj.pos;
	copy.dir = obj.dir;
	copy.k = obj.k;
	copy.vector = obj.vector;
	copy.r = obj.r;
	copy.t = obj.t;
	copy.vector = obj.vector;
	copy.mat = obj.mat;
	copy.plimit_active = obj.plimit_active;
	copy.plimit_valid = obj.plimit_valid;
	copy.plimit_type = obj.plimit_type;
	copy.nbr_limit = obj.nbr_limit;
	if (copy.plimit_active == 1)
		copy.plimit = copy_limit(obj);
	return (copy);
}

t_scene				copy_scene(t_scene scene)
{
	t_scene			copy;
	int				i;

	i = -1;
	copy.lights = (t_light *)malloc(scene.nbr_light * sizeof(t_light));
	while (++i < scene.nbr_light)
		copy.lights[i] = copy_light(scene.lights[i]);
	copy.obj = (t_obj *)malloc(scene.nbr_obj * sizeof(t_obj));
	i = -1;
	while (++i < scene.nbr_obj)
		copy.obj[i] = copy_objs(scene.obj[i]);
	copy.skybox = scene.skybox;
	copy.last = scene.last;
	copy.nbr_light = scene.nbr_light;
	copy.nbr_obj = scene.nbr_obj;
	copy.nbr_tot = scene.nbr_tot;
	copy.ambient = scene.ambient;
	copy.id = scene.id;
	copy.supersampling = scene.supersampling;
	copy.cam = scene.cam;
	copy.filters = scene.filters;
	return (copy);
}

t_rt				*copy_rt(t_rt *e)
{
	t_rt			*copy;

	copy = NULL;
	if ((copy = (t_rt *)malloc(sizeof(t_rt))) == NULL)
		exit(42);
	copy->scene = copy_scene(e->scene);
	copy->file.larg = e->file.larg;
	copy->file.haut = e->file.haut;
	copy->file.reso = e->file.reso;
	copy->file.aliasing = e->file.aliasing;
	return (copy);
}
