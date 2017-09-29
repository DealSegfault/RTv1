/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agfernan <agfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 15:28:19 by agfernan          #+#    #+#             */
/*   Updated: 2017/09/27 13:06:28 by mhalit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color		get_checker_col(t_checker check, t_vec3 pt)
{
	t_vec3	co;

	co.x = floorf(pt.x / check.l);
	co.y = floorf(pt.y / check.l);
	co.z = floorf(pt.z / check.l);
	co.z = (co.z < 0) ? co.z * -1 : co.z;
	co.y = (co.y < 0) ? co.y * -1 : co.y;
	co.x = (co.x < 0) ? co.x * -1 : co.x;
	if ((int)co.z % 2 == 0 || co.z == 0)
	{
		if (((int)co.x % 2 == 0 && (int)co.y % 2 == 0) ||
				((int)co.x % 2 != 0 && (int)co.y % 2 != 0))
			return (check.c1);
		else
			return (check.c2);
	}
	else
	{
		if (((int)co.x % 2 == 0 && (int)co.y % 2 == 0) ||
				((int)co.x % 2 != 0 && (int)co.y % 2 != 0))
			return (check.c2);
		else
			return (check.c1);
	}
}
