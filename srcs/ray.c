/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparigi <mparigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 14:55:55 by tfaure            #+#    #+#             */
/*   Updated: 2017/08/18 00:53:04 by rlecart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float	get_length(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_ray		c_ray(t_vec3 i, t_vec3 j)
{
	t_ray	ray;

	ray.pos = vec_new3(i.x, i.y, i.z);
	ray.dir = vec_norme3(vec_new3(j.x, j.y, j.z));
	return (ray);
}

t_color			skybox(t_rt *e, t_ray ray)
{
	t_color	color_sky;
	float	u;
	float	v;
	t_vec3	norm;

	if (!(e->scene.skybox.is_init))
		return ((t_color){0, 0, 0, 0});
	norm = vec_norme3(ray.dir);
	u = atan2(norm.x, norm.z) / (2 * M_PI) + 0.5;
	v = norm.y * 0.5 + 0.5;
	u = e->scene.skybox.width * (1 - u);
	v = e->scene.skybox.height * (1 - v);
	color_sky = get_text_color((int)u, (int)v, e->scene.skybox);
	return (color_sky);
}

t_color			get_text_color(int x, int y, t_texture tex)
{
	int			c;
	t_color		color;
	int			pos;

	if (x < tex.width && y < tex.height && x >= 0 && y >= 0)
	{
		pos = (x * tex.bpp / 8) + (y * tex.sizl);
		c = *(int *)&(tex.data[pos]);
		color.r = c / 65536 % 256;
		color.g = c / 256 % 256;
		color.b = c % 256;
		return (color);
	}
	return ((t_color){0, 0, 0, 0});
}