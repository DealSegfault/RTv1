/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_mapping.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlecart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 22:41:01 by rlecart           #+#    #+#             */
/*   Updated: 2017/09/27 02:55:44 by rlecart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_vec2	uv_sphere(t_vec3 norm)
{
	t_vec2	uv;

	uv.x = atan2(norm.x, norm.z) / (2 * M_PI) + 0.5;
	uv.y = norm.y * 0.5 + 0.5;
	return (uv);
}

t_vec2	uv_plane(t_vec3 poi, t_vec3 norm)
{
	t_vec2	uv;
	t_vec3	u_axis;
	t_vec3	v_axis;

	u_axis = vec_new3(norm.y, norm.z, -norm.x);
	v_axis = vec_tsub3(u_axis, norm);
	uv.x = vec_dot3(poi, u_axis);
	uv.y = vec_dot3(poi, v_axis);
	return (uv);
}

t_vec2	get_uv_obj(t_obj obj, t_vec3 poi, t_vec3 norm)
{
	t_vec2	uv;

	if (obj.type == SPHERE)
		uv = uv_sphere(norm);
	else if (obj.type == PLANE)
		uv = uv_plane(poi, norm);
	else
	{
		uv.x = 0;
		uv.y = 0;
	}
	return (uv);
}
