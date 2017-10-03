/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_complex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agfernan <agfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/03 19:17:01 by mhalit            #+#    #+#             */
/*   Updated: 2017/10/01 17:36:06 by agfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		create_dick(t_obj obj, t_rt *e, int i)
{
	float j;

	j = 1;
	e->scene.nbr_complex++;
	i += create_obj(SPHERE, e);
	SOBJ.pos = vec_new3(obj.pos.x - (obj.r * 1.5), obj.pos.y, obj.pos.z);
	SOBJ.r = obj.r * 1.5;
	SOBJ.color = obj.color;
	SOBJ.id = e->scene.nbr_complex;
	i += create_obj(SPHERE, e);
	SOBJ.pos = vec_new3(obj.pos.x + (obj.r * 1.5), obj.pos.y, obj.pos.z);
	SOBJ.r = obj.r * 1.5;
	SOBJ.color = obj.color;
	SOBJ.id = e->scene.nbr_complex;
	while (j < 4)
	{
		i += create_obj(SPHERE, e);
		SOBJ.pos = vec_new3(obj.pos.x, obj.pos.y - obj.r * 1.5 * j, obj.pos.z);
		SOBJ.r = obj.r * 1.5;
		SOBJ.color = obj.color;
		SOBJ.id = e->scene.nbr_complex;
		j += 0.50;
	}
}

static void		create_mickey(t_obj obj, t_rt *e, int i)
{
	e->scene.nbr_complex++;
	i += create_obj(SPHERE, e);
	SOBJ.pos = obj.pos;
	SOBJ.r = obj.r;
	SOBJ.color = obj.color;
	SOBJ.id = e->scene.nbr_complex;
	i += create_obj(SPHERE, e);
	SOBJ.pos = vec_new3(obj.pos.x + obj.r, obj.pos.y + obj.r, obj.pos.z);
	SOBJ.r = obj.r / 2;
	SOBJ.color = obj.color;
	SOBJ.id = e->scene.nbr_complex;
	i += create_obj(SPHERE, e);
	SOBJ.pos = vec_new3(obj.pos.x - obj.r, obj.pos.y + obj.r, obj.pos.z);
	SOBJ.r = obj.r / 2;
	SOBJ.color = obj.color;
	SOBJ.id = e->scene.nbr_complex;
}

void			get_new_obj_list(t_rt *e)
{
	int			i;
	int			len;
	t_obj		*new_list;

	i = 0;
	len = 0;
	while (i < e->scene.nbr_obj)
	{
		if (e->COBJ.type == MICKEY)
			len += 3;
		if (e->COBJ.type == DICK)
			len += 8;
		else
			len += 1;
		i++;
	}
	if (!(new_list = (t_obj *)malloc(sizeof(t_obj) * len)))
		exit(-42);
	i = -1;
	while (++i < e->scene.nbr_obj)
		new_list[i] = e->scene.obj[i];
	free(e->scene.obj);
	e->scene.obj = new_list;
}

void			create_complex(t_rt *e)
{
	int i;

	i = 0;
	get_new_obj_list(e);
	while (i < e->scene.nbr_obj)
	{
		if (e->COBJ.type == MICKEY)
			create_mickey(e->COBJ, e, i);
		if (e->COBJ.type == DICK)
			create_dick(e->COBJ, e, i);
		++i;
	}
}
