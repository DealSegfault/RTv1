#include "rt.h"

float		find_min_dist_for_refref(t_rt *e, int *a, t_ray ray)
{
	float min_dist;
	float	dist;
	int i;

	i = 0;
	dist = 0;
	min_dist = DIST_MAX;
	while (i < e->scene.nbr_obj)
	{
		if (i != e->scene.id)
		{
			dist = intersect_obj(ray, e->COBJ);
			if (dist < min_dist)
			{
				min_dist = dist;
				*a = i;
			}
		}
		i++;
	}
	return min_dist;
}

t_ray			get_refracted_ray(t_rt *e, t_ray rayon, t_vec3 poi)
{
	t_vec3 source;
	t_vec3 normale;
	t_ray ray;

	ray.pos = poi;
	normale = object_norm(e->scene.obj[e->scene.id], poi);
	source = rayon.dir;
	ray.dir = vec_scale3(vec_mul3(source, normale), e->scene.obj[e->scene.id].mat.refract);
	ray.dir = vec_mul3(ray.dir, normale);
	ray.dir = vec_norme3(vec_sub3(vec_scale3(source, e->scene.obj[e->scene.id].mat.refract+1), ray.dir));
	return (ray);
}

t_color			get_refracted_color(t_rt *e, t_vec3 poi, t_color base_color, int counter, t_ray rayon)
{

	float		min_dist;
	int         a;
	t_ray 		ray;
	t_color		final_color;
	t_vec3 		newpoi;
	float		taux_temp;

	if(counter == 0)
		return (base_color);
	counter--;
	ray = get_refracted_ray(e, rayon, poi);
	taux_temp = e->scene.obj[e->scene.id].mat.refract;
	min_dist = find_min_dist_for_refref(e, &a, ray);
	if(min_dist < DIST_MAX)
	{
		newpoi = vec_add3(ray.pos, vec_scale3(ray.dir, min_dist));
		final_color = get_color(e, e->scene.obj[a], newpoi);
		base_color = ft_map_color(base_color, final_color, taux_temp);
		e->scene.id = a;
		if (e->scene.obj[a].mat.reflex)
			return (get_reflected_color(e, newpoi, base_color, counter, ray));
		if (e->scene.obj[a].mat.refract)
			return (get_refracted_color(e, newpoi, base_color, counter, ray));
		return (base_color);
	}
	return ft_map_color(base_color, skybox(e, ray), taux_temp);
}