/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocojeda- <ocojeda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 12:28:36 by mhalit            #+#    #+#             */
/*   Updated: 2017/08/17 17:18:22 by ocojeda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "libft.h"
# include "mlx.h"
# include "libvec.h"
# include <math.h>
# include <stdio.h>
# include <pthread.h>
# include <fcntl.h>
# include <unistd.h>

# define AP 81
# define AM 75
# define HEIGHT 500
# define WIDTH 500
# define EPSILON 1e-9
# define EXTENSION ".rt"
# define ERR -1
# define END 0
# define OK 1
# define CONE 1
# define PLANE 2
# define SPHERE 3
# define CYLINDER 4
# define LIGHT 1
# define OBJ 2
# define BLACK		0
# define RED		1
# define GREEN		2
# define YELLOW		3
# define BLUE		4
# define MAGENTA	5
# define CYAN		6
# define WHITE		7

# define ESC		53
# define BACKSPACE	51
# define SPACE		49
# define LSHIFT		257
# define ENTER		36
# define KEY_1		18
# define KEY_2		19
# define KEY_3		20
# define KEY_4		21
# define PLUS		69
# define MINUS		78
# define UP			126
# define DOWN		125
# define LEFT		123
# define RIGHT		124
# define PAGE_UP	116
# define PAGE_DOWN	121
# define KEY_W		13
# define KEY_A		0
# define KEY_S		1
# define KEY_D		2

# define INIT env->mlx.init
# define WIN env->mlx.window
# define IMG env->mlx.image
# define SS (env->scene.supersampling)
# define HAUTEUR env->file.haut * SS
# define LARGEUR env->file.larg
# define SFILE env->file.path
# define POS env->scene.cam.ray.pos
# define DIR env->scene.cam.ray.pos
# define CAMRAY env->cam.ray
# define COLOR scene.obj[i].color
# define COBJ scene.obj[i]
# define CLIGHT scene.lights[i]
# define SOBJ env->scene.obj[env->scene.nbr_obj - 1]
# define SLIGHT env->scene.lights[env->scene.nbr_light - 1]
# define ABS(x) (x < 0 ? -x : x)
# define MAXOBJ 50
# define MAXLIGHT 21

/* 
*	DEF_super is 1 for on and 0 for off.
*/

# define W LARGEUR * SS
# define H HAUTEUR * SS

# define FOV 30
# define KEY_ESC 53
# define DIST_MAX 20000
# define DIST_MIN -80000
# define AMBIENT_LIGHT 50

# define AVERAGE(a, b)   ( ((((a) ^ (b)) & 0xfffefefeL) >> 1) + ((a) & (b)) )

typedef struct		s_ray
{
	t_vec3			pos;
	t_vec3			dir;
}					t_ray;

typedef struct		s_color
{
	float			b;
	float			g;
	float			r;
	float 			a;
}					t_color;

typedef struct		s_light
{
	int				is_init;
	t_ray			ray;
	t_color			color;
	float			intensity;
}					t_light;

typedef struct		s_camera
{
	t_ray			ray;
	float			focale;
	float			reso;
}					t_camera;

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

typedef struct		s_matiere
{
	float			amb;
	t_color			diffuse;
	float			reflex;
	float			specular;
	float			shininess;
	float			reflect;
	float			transparency;
	float			absorbtion;
	char			*coeff;
	char			opacite;
}					t_matiere;

typedef struct		s_calc
{
	float			a;
	float			b;
	float			c;
	float			d;
	float			t0;
	float			t1;
	float			disc;
	float			eq;
	t_vec3			len;
	float			sqrtdisc;
}					t_calc;

typedef struct		s_file
{
	char			*path;
	int				haut;
	int				larg;
}					t_file;

typedef struct		s_obj
{
	char			is_init;
	int				type;
	t_color			color;
	t_vec3			pos;
	t_vec3			dir;
	float			size;
	t_vec3			vector; //For Plane, Cylinder, Cone and Sphere
	t_vec3			maxp; //For Cylinder and Cone
	t_vec3			minp; //For Cone
	int				r;
	float			t;
	t_vec3			normal;
	t_matiere		mat;
}					t_obj;

typedef struct		s_scene
{
	t_light			*lights;
	t_obj			*obj;
	char			*last;
	int				nbr_light;
	int				nbr_obj;
	char			nbr_tot;
	int 			id;
	int				supersampling;
	t_camera		cam;
}					t_scene;

typedef struct		s_rt
{
	t_mlx			mlx;
	t_scene			scene;
	t_file			file;
	unsigned int 	*img_temp;
}					t_rt;

void				display_args(void);
t_matiere			create_matiere(void);
int					set_obj(t_rt *env, char **a);
int					set_light(t_rt *env, char **a);
int					set_camera(t_rt *env, char **a);
int					set_last(t_rt *env, char **params);
int					camera_create(t_rt *env);
int					create_obj(int type, t_rt *env);
int					create_light(t_rt *env);
t_color				c_color(float r, float g, float b);
int					parse_args(char **argv, int argc, t_rt *env);
int					parse_obj(char *path, t_rt *env);
void				store_type_or_data(char *line, t_rt *env);
void				frame(t_rt *env);
void				mlx_pixel(int x, int y, t_rt *env, int color);
void				anti_aliasing_on(t_rt *env);
void				anti_aliasing_off(t_rt *env);
//OLD

unsigned int		ret_colors(t_color color);
t_ray				c_ray(t_vec3 i, t_vec3 j);
t_color				raytrace(int x, int y, t_rt *env);
void				super_sampler(t_rt *env);
void				anti_supersampler(t_rt *env);
float				intersect_sphere(t_ray ray, t_obj sphere);
int					key_hook(int keycode, t_rt *e);
t_color				color_mult(t_color color, float taux);
float				get_length(t_vec3 v);
float				intersect_plane(t_ray ray, t_obj sphere);
float				intersect_cylinder(t_ray ray, t_obj cylinder);
t_color				copy_color(t_color color);
float				intersect_cone(t_ray ray, t_obj cone);
float				intensity_cone(t_rt *e, t_vec3 poi,
						t_obj cone, t_light light);
float				intensity_sphere(t_rt *e, t_vec3 poi,
						t_obj sphere, t_light light);
float				intensity_plane(t_rt *e, t_vec3 poi,
						t_obj plane, t_light light);
float				intensity_cylinder(t_rt *e, t_vec3 poi,
						t_obj cylinder, t_light light);
t_color				get_color(t_rt *e, t_obj obj, t_vec3 poi);
float				get_min_dist(t_rt *e, t_ray ray, int cangoneg);
int					obj_in_shadow(t_rt *e, t_vec3 poi, t_light light);
float				get_res_of_quadratic(float a, float b, float c);

#endif
