/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ocl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 02:51:19 by mhalit            #+#    #+#             */
/*   Updated: 2017/08/17 21:21:50 by rlecart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color			c_color(float r, float g, float b)
{
	t_color		color;

	color.r = ft_map(r, 255, 0, 0.5);
	color.g = ft_map(g, 255, 0, 0.5);
	color.b = ft_map(b, 255, 0, 0.5);
	return (color);
}

t_matiere	create_matiere(void)
{
	t_matiere	mat;

	mat.reflex = 0;
	mat.specular = 0;
	mat.opacite = 1;
	return (mat);
}

int			camera_create(t_rt *e)
{
	e->scene.cam.ray.pos = vec_new3(0, 0, -2000);
	e->scene.cam.ray.dir = vec_new3(0, 0, 1);
	e->scene.cam.focale = 1;
	e->scene.cam.reso = 300;
	return (1);
}

int			create_obj(int type, t_rt *e)
{
	int		i;

	i = e->scene.nbr_obj;
	e->COBJ.is_init = 1;
	e->COBJ.type = type;
	e->COBJ.color = c_color(255, 255, 255);
	e->COBJ.pos = vec_new3(0, 0, 0);
	e->COBJ.dir = vec_new3(0, 0, 0);
	e->COBJ.angle = 0;
	e->COBJ.maxp = vec_new3(0, 0, 0);
	e->COBJ.minp = vec_new3(0, 0, 0);
	e->COBJ.r = 0;
	e->COBJ.t = -1;
	e->COBJ.mat = create_matiere();
	e->scene.nbr_obj++;
	return (1);
}

int			create_light(t_rt *e)
{
	int		i;

	i = e->scene.nbr_light;
	e->CLIGHT.is_init = 1;
	e->CLIGHT.ray.pos = vec_new3(0, 0, 0);
	e->CLIGHT.ray.dir = vec_new3(0, 0, 0);
	e->CLIGHT.color = c_color(255, 255, 255);
	e->CLIGHT.intensity = 0;
	e->scene.nbr_light++;
	return (1);
}
