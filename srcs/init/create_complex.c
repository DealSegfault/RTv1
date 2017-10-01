/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_complex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparigi <mparigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/03 19:17:01 by mhalit            #+#    #+#             */
/*   Updated: 2017/09/23 18:26:07 by mparigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		create_dick(t_obj obj, t_rt *e, int i)
{
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

	float j = 1;
	while (j < 4)
	{
		i += create_obj(SPHERE, e);
		SOBJ.pos = vec_new3(obj.pos.x , obj.pos.y - obj.r * 1.5 * j, obj.pos.z);
		SOBJ.r = obj.r * 1.5;
		SOBJ.color = obj.color;
		SOBJ.id = e->scene.nbr_complex;
		j+= 0.50;
	}
}

static void		create_mickey(t_obj obj, t_rt *e, int i)
{
	printf("(%d)\n", e->scene.nbr_complex);
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

void			create_complex(t_rt *e)
{
	int i;

	i = 0;
	printf("MICKEY      = (%d)\n", MICKEY);
	printf("DICK        = (%d)\n\n", DICK);
	while (i < e->scene.nbr_obj)
	{
		printf("i       = (%d)\n", i);
		printf("nbr_obj = (%d)\n", e->scene.nbr_obj);
		printf("type    = (%d)\n\n",  e->COBJ.type);
		if (e->COBJ.type == MICKEY)
			create_mickey(e->COBJ, e, i);
		if (e->COBJ.type == DICK)
			create_dick(e->COBJ, e, i);
		++i;
	}
}
