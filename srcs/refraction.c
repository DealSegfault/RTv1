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

t_color			get_refracted_color(t_rt *e, t_vec3 poi, t_color base_color, t_reflect ref)
{
	int         a;
	t_color		final_color;
	t_color		temp_color1;
	t_vec3 		newpoi;
	float		taux_temp;
	float		distance_rate;
	

	if(ref.counter == 0)
		return (base_color);
	ref.counter--;
	ref.new_ray = get_refracted_ray(e, ref.ray, poi);
	taux_temp = e->scene.obj[e->scene.id].mat.refract;
	ref.min_dist = find_min_dist_for_refref(e, &a, ref.new_ray);
	ref.total_distance += ref.min_dist;
	distance_rate = ft_map(ref.min_dist, ref.total_distance, 0, 1) * taux_temp;
	if(ref.min_dist < DIST_MAX)
	{
		newpoi = vec_add3(ref.new_ray.pos, vec_scale3(ref.new_ray.dir, ref.min_dist));
		final_color = get_color(e, e->scene.obj[a], newpoi);
		base_color = ft_map_color(base_color, final_color, taux_temp);
		e->scene.id = a;
		ref.ray = c_ray(poi, ref.new_ray.dir);
		if (e->scene.obj[a].mat.refract)
		{
			if(e->scene.obj[a].mat.refract == 1)
				base_color = c_color(0,0,0);
			distance_rate *= e->scene.obj[a].mat.refract;
			temp_color1 = get_refracted_color(e, newpoi, base_color, ref);
			return (ft_map_color(base_color, temp_color1, distance_rate));
		}
		else if (e->scene.obj[a].mat.reflex)
		{
			if(e->scene.obj[a].mat.reflex == 1)
			base_color = c_color(0,0,0);
			distance_rate *= e->scene.obj[a].mat.reflex;
			temp_color1 = get_reflected_color(e, newpoi, base_color, ref);
			return (ft_map_color(base_color, temp_color1, distance_rate));	
		}
		return (base_color);
	}
	return ft_map_color(base_color, skybox(e, ref.new_ray), taux_temp);
}