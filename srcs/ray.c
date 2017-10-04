/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparigi <mparigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 18:56:25 by mhalit            #+#    #+#             */
/*   Updated: 2017/10/04 18:21:46 by mparigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float			get_length(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_ray			c_ray(t_vec3 i, t_vec3 j)
{
	t_ray		ray;

	ray.pos = vec_new3(i.x, i.y, i.z);
	ray.dir = vec_norme3(vec_new3(j.x, j.y, j.z));
	return (ray);
}

char			color_is_black(t_color *color)
{
	int		nbr;

	nbr = color->r + color->b + color->g;
	if (!nbr)
		*color = (t_color){1, 1, 1, 0};
	return ((!nbr) ? 1 : 0);
}

t_color			skybox(t_rt *e, t_ray ray)
{
	t_color		color_sky;
	t_vec2		uv;
	t_vec3		norm;
	int			i;
	float		intensity;

	i = -1;
	intensity = 0;
	color_sky = (t_color){0, 0, 0, 0};
	while (++i < e->scene.nbr_light)
		intensity += dazzling_light(e, e->CLIGHT, vec_norme3(ray.dir));
	if (!(e->scene.skybox.is_init))
		return (color_mult((t_color){0, 0, 0, 0}, intensity, 0));
	norm = vec_norme3(ray.dir);
	uv.x = atan2(norm.x, norm.z) / (2 * M_PI) + 0.5;
	uv.y = norm.y * 0.5 + 0.5;
	uv.x = e->scene.skybox.width * (1 - uv.x);
	uv.y = e->scene.skybox.height * (1 - uv.y);
	color_sky = get_text_color((int)uv.x, (int)uv.y, e->scene.skybox);
	intensity *= (color_is_black(&color_sky)) ? 100 : 5;
	return (color_mult(color_sky, 1 + intensity, 0));
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
