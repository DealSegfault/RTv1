/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfaure <tfaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 12:28:36 by mhalit            #+#    #+#             */
/*   Updated: 2017/08/24 22:58:46 by mhalit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "libft.h"
# include "../libs/minilibx/mlx.h"
# include "libvec.h"
# include <math.h>
# include <stdio.h>
# include <pthread.h>
# include <fcntl.h>
# include <unistd.h>

# include "parser.h"
# include "tree.h"
# include "xmlIO.h"
# include "xinclude.h"
# include "valid.h"
# include "xmlschemas.h"
# include "xmlstring.h"
# include "xmlreader.h"

# include <gtk/gtk.h>

# define RT_XSD "validator.xsd"
# define RT_DTD "validator.dtd"
# define STD_ERR 2
# define ROOT_NAME "scene"

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
# define MICKEY 5
# define DICK 6

# define LIGHT 1
# define OBJ 2

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
# define KEY_N8		91
# define KEY_N2		84
# define INIT e->mlx.init
# define WIN e->mlx.window
# define IMG e->mlx.image
# define DATA e->mlx.data
# define LINE e->mlx.size_l
# define RES e->file.reso
# define ALIASING e->file.aliasing
# define SS (e->scene.supersampling)
# define HAUTEUR e->file.haut
# define LARGEUR e->file.larg
# define SFILE e->file.path
# define CPOS e->scene.cam.ray.pos
# define CDIR e->scene.cam.ray.dir
# define CAMRAY e->cam.ray
# define COLOR scene.obj[i].color
# define COBJ scene.obj[i]
# define CLIGHT scene.lights[i]
# define SOBJ e->scene.obj[e->scene.nbr_obj - 1]
# define SLIGHT e->scene.lights[e->scene.nbr_light - 1]
# define AMBIENT_LIGHT e->scene.ambient
# define MAXOBJ 50
# define MAXLIGHT 21

# define WSS (LARGEUR * SS)
# define HSS (HAUTEUR * SS)
# define RES_H (HAUTEUR / RES)
# define RES_W (LARGEUR / RES)

# define DEFAULT_SUPERSAMPLING 0
# define FOVL 110
# define FOVH 90
# define KEY_ESC 53
# define DIST_MAX 20000
# define DIST_MIN -80000
# define EPSILON 1e-9
# define AVERAGE(a, b)   ( ((((a) ^ (b)) & 0xfffefefeL) >> 1) + ((a) & (b)) )
# define FT_MIN(x, y) ((x < y) ? x : y)
# define FT_MAX(x, y) ((x > y) ? x : y)

# define NB_THREADS 8
# define GTK_W 300
# define GTK_H 200	

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

typedef struct	s_texture
{
	void		*img;
	char		*data;
	int			bpp;
	int			size_l;
	int			endian;
	int			width;
	int			height;
}				t_texture;

typedef struct		s_matiere
{
	t_color			diffuse;
	float			reflex;
	float			specular;
	float			shininess;
	float			reflect;
	float			transparency;
	float			absorbtion;
	char			*coeff;
	char			opacite;
	t_texture		texture;
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
	int 			fdp;
	int 			reso;
	int				aliasing;
}					t_file;

typedef struct		s_obj
{
	char			is_init;
	int				type;
	t_color			color;
	t_vec3			pos;
	t_vec3			dir;
	float			angle;
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
	float			ambient;
	int				nbr_light;
	int				nbr_obj;
	char			nbr_tot;
	int 			id;
	int				supersampling;
	int 			filters;
	t_camera		cam;
}					t_scene;

typedef struct		s_screen
{
	float			pos;
	float			pitch;
	float			yaw;
}					t_screen;

typedef struct		s_mthread
{
	float 			y;
	float			max_y;
	float			h;
	float			w;
	t_color			*colors;
}					t_mthread;

typedef struct		s_gtk_input
{
	gint			max_size;
	gint			max_char;
	gchar			*placeholder;
	gchar   		*deflaut_value;
}					t_gtk_input;

typedef struct		s_gtk_win
{
	GtkWidget 		*window;
	GtkWidget		*layout;
}					t_gtk_win;

typedef struct		s_gtk_settings
{
	int 			width;
	int 			height;
	int 			res;
	GtkWidget 		*anti_aliasing;
}					t_gtk_settings;

typedef struct		s_gtk
{
	t_gtk_win		menu;
	t_gtk_win		settings;
	t_gtk_settings	values;
}					t_gtk;

typedef struct		s_rt
{
	t_mlx			mlx;
	t_gtk			gtk;
	t_scene			scene;
	t_file			file;
	t_mthread		thread;
	unsigned int	*img_temp;
	int				started;
}					t_rt;

void				display_args(void);
t_matiere			create_matiere(void);
int					set_obj(t_rt *e, char **a);
int					set_light(t_rt *e, char **a);
int					set_camera(t_rt *e, char **a);
int					set_last(t_rt *e, char **params);
int					camera_create(t_rt *e);
int					create_obj(int type, t_rt *e);
int					create_light(t_rt *e);
void 				create_complex(t_rt *e);
t_color				c_color(float r, float g, float b);
int					parse_args(char **argv, int argc, t_rt *e);
int					parse_obj(t_rt *e, int fd);
void				store_type_or_data(char *line, t_rt *e);
void				frame(t_rt *e);
void				mlx_pixel(int x, int y, t_rt *e, int color);
void      			fl_sepia_apply(t_rt *e);
void       			fl_black_and_white(t_rt *e);
void				fl_border_limits(t_rt *e);
void				fl_border(t_rt *e);
void				fl_revers(t_rt *e);

//hook

void				mv_plus_minus(t_rt *e, float *a, float value, int bol);
void				udlr_(int keycode, t_rt *e);
int					key_hook(int keycode, t_rt *e);
void 				wasd_(int keycode, t_rt *e);
void				resolution(int keycode, t_rt *e);
void				exportimg(int keycode, t_rt *e);
void				numeric_(int keycode, t_rt *e);


//Multithreading

t_light				copy_light(t_light light);
t_obj				copy_objs(t_obj obj);
t_scene				copy_scene(t_scene scene);
t_rt				*copy_rt(t_rt *e);
void				*drawline(void *arg);
t_rt            	**launch_thread(t_rt *env);
//OLD


//Beta option

void  				pixel_to_image(int x, int y, t_rt *e, int color);

unsigned int		ret_colors(t_color color);
t_ray				c_ray(t_vec3 i, t_vec3 j);
t_vec3				get_vec(int x, int y, t_vec3 dir, t_rt *e);
t_color				raytrace(int x, int y, t_rt *e);
t_color				raytrace2(int x, int y, t_rt *e);
void				super_sampler(t_rt *e);
void				anti_supersampler(t_rt *e);
void				anti_aliasing_on(t_rt *e, unsigned int *img_temp);
void				anti_aliasing_off(t_rt *e);
float				intersect_sphere(t_ray ray, t_obj sphere);
t_color				color_mult(t_color color, float taux);
float				get_length(t_vec3 v);
float				intersect_plane(t_ray ray, t_obj sphere);
float				intersect_cylinder(t_ray ray, t_obj cylinder);
t_color				copy_color(t_color color);
float				intersect_cone(t_ray ray, t_obj cone);
float				intersect_cone2(t_ray ray, t_obj obj);
float				intensity_cone(t_rt *e, t_vec3 poi,
						t_obj cone, t_light light);
float				intensity_sphere(t_vec3 poi,
						t_obj sphere, t_light light);
float				intensity_plane(t_rt *e, t_vec3 poi,
						t_obj plane, t_light light);
float				intensity_cylinder(t_rt *e, t_vec3 poi,
						t_obj cylinder, t_light light);
t_color				get_color(t_rt *e, t_obj obj, t_vec3 poi);
float				get_min_dist(t_rt *e, t_ray ray, int cangoneg);
int					obj_in_shadow(t_rt *e, t_vec3 poi, t_light light);
float				get_res_of_quadratic(float a, float b, float c);

int					xsd_read_error();
int					doChecks(xmlDocPtr doc);
void				xml_read_error();
xmlDocPtr			getdoc(char *docname);


//GTK
int					parse_filename(t_rt *e, char *filename);
void 				ft_start_rt(t_rt *e);
void				init_rt(t_rt *e);

void 				ft_gtk_start_launcher(t_rt *e);
void 				ft_gtk_start_settings(t_rt *e);
void 				ft_settings(t_rt *e);
void 				ft_gtk_launcher(t_rt *e);

GtkWidget 			*new_window(gint w, gint h, gchar *name);
GtkWidget			*new_input(t_gtk_input *data);
GtkWidget			*new_txt(gchar *str);
GtkWidget			*new_btn(int x, int y, char *name);
void 				ft_gtk_link_css(GtkWidget *window, gchar *css);

#endif
