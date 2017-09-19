/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_complex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/03 19:17:01 by mhalit            #+#    #+#             */
/*   Updated: 2017/09/03 19:17:03 by mhalit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		create_dick(t_obj obj, t_rt *e, int i)
{
 	i += create_obj(SPHERE, e);
	SOBJ.pos = vec_new3(obj.pos.x - (obj.r * 1.5), obj.pos.y, obj.pos.z);
	SOBJ.r = obj.r * 1.5;
	SOBJ.color = obj.color;

   	i += create_obj(SPHERE, e);
	SOBJ.pos = vec_new3(obj.pos.x + (obj.r * 1.5), obj.pos.y, obj.pos.z);
	SOBJ.r = obj.r * 1.5;
	SOBJ.color = obj.color;

    float j = 1;
    while (j < 4)
    {
        i += create_obj(SPHERE, e);
        SOBJ.pos = vec_new3(obj.pos.x , obj.pos.y - obj.r * 1.5 * j, obj.pos.z);
        SOBJ.r = obj.r * 1.5;
        SOBJ.color = obj.color;
        j+= 0.40;
    }
}

static void		create_mickey(t_obj obj, t_rt *e, int i)
{
	i += create_obj(SPHERE, e);
	SOBJ.pos = obj.pos;
	SOBJ.r = obj.r;
	SOBJ.color = obj.color;
	printf("%d\n", i);

 	i += create_obj(SPHERE, e);
	SOBJ.pos = vec_new3(obj.pos.x - obj.r, obj.pos.y - obj.r, obj.pos.z);
	SOBJ.r = obj.r / 2;
	SOBJ.color = obj.color;

 	i += create_obj(SPHERE, e);
	SOBJ.pos = vec_new3(obj.pos.x + obj.r, obj.pos.y - obj.r, obj.pos.z);
	SOBJ.r = obj.r / 2;
	SOBJ.color = obj.color;
}

void create_complex(t_rt *e)
{
		int i;

		i = 0;
		while (i < e->scene.nbr_obj)
		{
			if (e->COBJ.type == MICKEY)
				create_mickey(e->COBJ, e, i);
            if (e->COBJ.type == DICK)
				create_dick(e->COBJ, e, i);
			++i;
		}
}
