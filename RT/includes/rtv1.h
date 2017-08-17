/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocojeda- <ocojeda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 14:37:39 by tfaure            #+#    #+#             */
/*   Updated: 2017/08/17 17:18:27 by ocojeda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef RTV1_H
# define RTV1_H

# include "libft.h"
# include "libvec.h"
# include <math.h>
# include "mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

/*
** if we want to switch on or off supersampler we need to change
** SS value. 1 for off, 2 for on.

# define FOV 30
# define KEY_ESC 53
# define DIST_MAX 20000
# define DIST_MIN -80000
# define AMBIENT_LIGHT 50

/*
** Compute the average color between two 24-bits RGB colors
** https://www.compuphase.com/graphic/scale3.htm
*/
//# define AVERAGE(a, b)   ( ((((a) ^ (b)) & 0xfffefefeL) >> 1) + ((a) & (b)) )

//# define AVERAGE(a, b)   ( ((((a) ^ (b)) & 0xfffefefeL) >> 1) + ((a) + (b)) ) //effect bizarre

enum				e_type
{
	PLANE = 2,
	SPHERE,
	CYLINDER,
	CONE
}					;

typedef struct		s_mlx
{
	void			*init;
	void			*window;
	void			*image;
	char			*data;
	int				bpp;
	int				size_l;
	int				endian;
}					t_mlx;


typedef struct		s_color
{
	double			r;
	double			g;
	double			b;
}					t_color;

typedef struct		s_setup
{
}					t_setup;

typedef struct		s_ray
{
	t_vec3d			pos;
	t_vec3d			dir;
}					t_ray;

// typedef struct		s_light
// {
// 	double			intensity;
// 	t_vec3d			origin;
// 	struct s_light	*next;
// }					t_light;

typedef struct		s_light
{
	int				is_init;
	t_ray			ray;
	t_color			color;
	double			intensity;
	struct s_light 	*next;
}					t_light;

typedef struct		s_obj
{
	int				type;
	double			r;
	t_vec3d			normal;
	t_vec3d			pos;
	t_vec3d			dir;
	t_color			color;
	struct s_object	*next;
}					t_obj;

typedef struct		s_camera
{
	t_ray			ray;
	float			focale;
	float			reso;
}					t_camera;

typedef struct		s_scene
{
	t_light			*lights;
	int				supersampling;
	t_camera		camera;
	t_obj			*obj;
	char			*last;
	int				nbr_light;
	int				nbr_obj;
	char			nbr_tot;
	t_camera		cam;
}					t_scene;

typedef struct		s_env
{
	t_mlx 			mlx;
	t_scene			scene;
	t_light			*light;
	unsigned int	*img_temp;
	t_obj			*obj;
	int				nbline;
	int				fd;
}					t_rt;

unsigned int		ret_colors(t_color color);
t_ray				c_ray(t_vec3d i, t_vec3d j);
t_color				c_color2(double r, double g, double b);
void				set_win_img(t_rt *e);
int					raytrace2(t_rt *e);
void				super_sampler(t_rt *e);
void				anti_supersampler(t_rt *e);
double				intersect_sphere(t_ray ray, t_obj sphere);
int					key_hook(int keycode, t_rt *e);
t_color				*color_mult(t_color color, double taux);
double				get_length(t_vec3d v);
double				intersect_plane(t_ray ray, t_obj sphere);
double				intersect_cylinder(t_ray ray, t_obj cylinder);
t_color				*copy_color(t_color color);
double				intersect_cone(t_ray ray, t_obj cone);
double				intensity_cone(t_rt *e, t_vec3d poi,
						t_obj cone, t_light light);
double				intensity_sphere(t_rt *e, t_vec3d poi,
						t_obj sphere, t_light light);
double				intensity_plane(t_rt *e, t_vec3d poi,
						t_obj plane, t_light light);
double				intensity_cylinder(t_rt *e, t_vec3d poi,
						t_obj cylinder, t_light light);
double				get_min_dist(t_rt *e, t_ray ray, t_obj **closest, int cangoneg);
int					obj_in_shadow(t_rt *e, t_vec3d poi, t_light light);
double				get_res_of_quadratic(double a, double b, double c);

/*
** Parser
*/

t_rt				*parse(char *scene);
void				syntax_error(char *line, char *explain, int nbline);
void				unknown_setting(char *line, int nbline);
char				*trim_setting(t_rt *e, char *setting);
char				*trim_option(t_rt *e, char *option, char **arg);
void				dispatch(t_rt *e, char *line);
void				set_sphere(t_rt *e);
void				set_plane(t_rt *e);
void				set_plane_data(t_obj *plane);
void				set_cylinder(t_rt *e);
void				set_cone(t_rt *e);
void				set_camera2(t_rt *e);
void				set_light2(t_rt *e);
void				set_supersampling(t_rt *e, char *line);
t_vec3d				set_vec3d(t_rt *e, char *arg);
t_color				set_color(t_rt *e, char *arg);
void				unknown_option(char *line, int nbline, char *caller);
void				set_first_obj(t_rt *e, t_obj *obj);
void				set_first_light(t_rt *e, t_light *light);

#endif
