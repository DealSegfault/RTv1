/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libvec.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 13:11:14 by mhalit            #+#    #+#             */
/*   Updated: 2017/08/09 09:05:02 by mhalit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBVEC_H
# define LIBVEC_H
# include <math.h>

typedef struct	s_vec3
{
	float		x;
	float		y;
	float		z;
	float		m;
}				t_vec3;

typedef struct	s_vec3d
{
	double		x;
	double		y;
	double		z;
	double		m;
}				t_vec3d;

double			vec_dot3(t_vec3 u, t_vec3 v);
t_vec3			vec_scale3(t_vec3 u, float r);
t_vec3			vec_new3(float x, float y, float z);
t_vec3			vec_mul3(t_vec3 u, t_vec3 v);
t_vec3			vec_div3(t_vec3 u, t_vec3 v);
t_vec3			vec_add3(t_vec3 u, t_vec3 v);
t_vec3			vec_sub3(t_vec3 u, t_vec3 v);
t_vec3			vec_tsub3(t_vec3 u, t_vec3 v);
t_vec3			vec_inv3(t_vec3 u);
t_vec3			vec_norme3(t_vec3 u);
t_vec3d			vec_scale3d(t_vec3d u, double r);
t_vec3d			vec_new3d(double x, double y, double z);
t_vec3d			vec_mul3d(t_vec3d u, t_vec3d v);
t_vec3d			vec_div3d(t_vec3d u, t_vec3d v);
t_vec3d			vec_add3d(t_vec3d u, t_vec3d v);
t_vec3d			vec_sub3d(t_vec3d u, t_vec3d v);
t_vec3d			vec_tsub3d(t_vec3d u, t_vec3d v);
t_vec3d			vec_inv3d(t_vec3d u);
t_vec3d			vec_norme3d(t_vec3d u);
#endif
