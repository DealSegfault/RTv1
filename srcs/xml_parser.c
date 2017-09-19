/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agfernan <agfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 11:35:38 by agfernan          #+#    #+#             */
/*   Updated: 2017/09/19 06:12:40 by agfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			ft_lstfree(t_list **lst)
{
	if (*lst)
	{
		ft_lstfree(&((*lst)->next));
		free(*lst);
		*lst = NULL;
	}
}

void			ft_lstpush(t_list **alst, t_list *new)
{
	t_list *temp;

	new->next = NULL;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	temp = *alst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

unsigned int	ft_lstlen(t_list *lst)
{
	unsigned int len;

	len = 0;
	if (!lst)
		return (-1);
	while (lst)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}

void			get_nodes_by_name(xmlNodePtr cur, char *node_name, t_list **lst)
{
	t_list	*new;

	while (cur)
	{
		if ((!xmlStrcmp(cur->name, (const xmlChar *)node_name)))
		{
			printf("added node : %s\n", cur->name);
			new = ft_lstnew((void *)cur, sizeof(*cur));
			ft_lstpush(lst, new);
		}
		get_nodes_by_name(cur->children, node_name, lst);
		cur = cur->next;
	}
}

xmlDocPtr		getdoc(char *docname)
{
	xmlDocPtr doc;

	doc = xmlReadFile(docname, NULL, 0);
	if (doc == NULL)
	{
		ft_putendl_fd("Wrong xml file\n", STD_ERR);
		return (NULL);
	}
	return (doc);
}

t_list			*get_object_nodes(xmlDocPtr doc)
{
	t_list		*lst;
	t_list		*lst2;
	t_list		*new;
	xmlNodePtr	temp;

	if (!doc)
		return (NULL);
	lst = NULL;
	lst2 = NULL;
	get_nodes_by_name(xmlDocGetRootElement(doc), "objects", &lst);
	temp = ((xmlNodePtr)lst->content)->children;
	while (temp)
	{
		ft_putendl((char *)temp->name);
		new = ft_lstnew((void *)temp, sizeof(*temp));
			ft_lstpush(&lst2, new);
		temp = temp->next;
	}
	return (lst2);
}

xmlNodePtr		get_lights(xmlDocPtr doc)
{
	t_list		*lst;
	xmlNodePtr	lights;

	get_nodes_by_name(xmlDocGetRootElement(doc), "lights", &lst);
	lights = (xmlNodePtr)lst->content;
	return (lights->children);
}

t_obj				create_obj_xml(int type)
{
	t_obj new;

	new.is_init = 1;
	new.type = type;
	new.color = c_color(255, 255, 255);
	new.pos = vec_new3(0, 0, 0);
	new.dir = vec_new3(0, 0, 0);
	new.angle = 0;
	new.maxp = vec_new3(0, 0, 0);
	new.minp = vec_new3(0, 0, 0);
	new.r = 0;
	new.t = -1;
	new.mat = create_matiere();
	return (new);
}

int				has_attr(xmlNodePtr a_node, xmlChar *attr)
{
	if (!xmlGetProp(a_node, attr))
		return (0);
	return (1);
}

xmlNodePtr		has_child(xmlNodePtr a_node, char *attr)
{
	xmlChar		*cast;
	xmlNodePtr	cur;

	cur = a_node->children;
	cast = (xmlChar *)attr;
	while (cur)
	{
		if (!xmlStrcmp(cur->name, cast))
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}

/*
TODO: Plan d'attaque: 
	- on fait le parsing des attributs eventuels => tout ce qu'il y a dans obj qui n'est pas une struct contenant plusieurs elements.
	- on creer la fonction de parsing des elements complexes (genre pos, dir, matiere, des balises qui elles memes vont avoir plusieurs attibuts) sous la forme "parsing_nomDeBalise(xmlNodePtr noeud_a_parser)".
	possibilité de factorisation avec un pointeur sur fonction passé en param

*/

t_color			parse_color(xmlNodePtr node)
{
	t_color color;

	color = c_color(ft_atoi((char *)xmlGetProp(node, BAD_CAST"r")),
		ft_atoi((char *)xmlGetProp(node, BAD_CAST"g")) , ft_atoi((char *)xmlGetProp(node, BAD_CAST"b")));
	return (color);
}

int				parse_mat(t_obj *obj, xmlNodePtr node)
{
	xmlChar		*val;

	if ((val = xmlGetProp(node, BAD_CAST"amb")))
		(*obj).mat.amb = ft_atof((char *)val);
	if ((val = xmlGetProp(node, BAD_CAST"reflex")))
		(*obj).mat.reflex = ft_atof((char *)val);
	if ((val = xmlGetProp(node, BAD_CAST"specular")))
		(*obj).mat.specular = ft_atof((char *)val);
	if ((val = xmlGetProp(node, BAD_CAST"shininess")))
		(*obj).mat.shininess = ft_atof((char *)val);
	if ((val = xmlGetProp(node, BAD_CAST"reflect")))
		(*obj).mat.reflect = ft_atof((char *)val);
	if ((val = xmlGetProp(node, BAD_CAST"transparency")))
		(*obj).mat.transparency = ft_atof((char *)val);
	if ((val = xmlGetProp(node, BAD_CAST"absorption")))
		(*obj).mat.absorbtion = ft_atof((char *)val);
	return (1);
}

t_vec3			get_vec_from_node(xmlNodePtr node)
{
	t_vec3 new;

	new.x = atof((char *)(xmlGetProp(node, BAD_CAST"x")));
	new.y = atof((char *)(xmlGetProp(node, BAD_CAST"y")));
	new.z = atof((char *)(xmlGetProp(node, BAD_CAST"z")));
	return (new);
}

int				parse_obj_node(t_obj *obj, xmlNodePtr node)
{
	xmlChar		*val;
	xmlNodePtr	child;

	if ((val = xmlGetProp(node, BAD_CAST"radius")))
		(*obj).r = ft_atof((char *)val);
	if ((val = xmlGetProp(node, BAD_CAST"angle")))
		(*obj).r = ft_atoi((char *)val) / 180 * M_PI;
	if ((child = has_child(node, "pos")))
		(*obj).pos = get_vec_from_node(child);
	if ((child = has_child(node, "dir")))
		(*obj).dir = get_vec_from_node(child);
	if ((child = has_child(node, "vector")))
		(*obj).vector = get_vec_from_node(child);
	if ((child = has_child(node, "maxp")))
		(*obj).maxp = get_vec_from_node(child);
	if ((child = has_child(node, "minp")))
		(*obj).minp = get_vec_from_node(child);
	if ((child = has_child(node, "matiere")))
		parse_mat(obj, child);
	if ((child = has_child(node, "color")))
		(*obj).color = parse_color(child);
	return(1);
}

int				parse_light_node(t_light *light, xmlNodePtr node)				
{
	xmlChar		*val;
	xmlNodePtr	child;

	if	((val = xmlGetProp(node, BAD_CAST"intensity")))
		(*light).intensity = atof((char *)val);
	if ((child = has_child(node, "pos")))
		(*light).ray.pos = get_vec_from_node(child);
	if ((child = has_child(node, "color")))
		(*light).color = parse_color(child);
	return (1);
}

t_obj			get_obj(xmlNodePtr node)
{
	t_obj new;

	if (!xmlStrcmp(node->name, BAD_CAST"sphere"))
		new = create_obj_xml(SPHERE);
	if (!xmlStrcmp(node->name, BAD_CAST"plane"))
		new = create_obj_xml(PLANE);
	if (!xmlStrcmp(node->name, BAD_CAST"cone"))
		new = create_obj_xml(CONE);
	if (!xmlStrcmp(node->name, BAD_CAST"cylindre"))
		new = create_obj_xml(CYLINDER);
	parse_obj_node(&new, node);
	return (new);
}

t_light			get_light(xmlNodePtr node)
{
	t_light light;

	light.is_init = 1;
	light.ray.pos = vec_new3(0, 0, 0);
	light.ray.dir = vec_new3(0, 0, 0);
	light.color = c_color(255, 255, 255);
	light.intensity = 0;
	parse_light_node(&light, node);
	return (light);
}

int			create_objs(t_rt *e, t_list *lst)
{
	int i;

	i = 0;
	e->scene.nbr_obj = ft_lstlen(lst);
	e->scene.obj = (t_obj *)malloc(sizeof(t_obj) * e->scene.nbr_obj);
	if (!e->scene.obj)
		exit(ERR);
	while (lst)
	{
		e->COBJ = get_obj((xmlNodePtr)lst->content);
		lst = lst->next;
		i++;
	}
	ft_lstfree(&lst);
	return (1);
}

int				set_camera_xml(t_rt *e, xmlNodePtr cam_node)
{
	xmlNodePtr child;

	camera_create(e);
	child = cam_node->children;
	e->scene.cam.ray.pos = get_vec_from_node(child);
	child = child->next;
	e->scene.cam.ray.dir = get_vec_from_node(child);
	// e->scene.cam.fov = ft_atoi((char *)xmlGetProp(cam_node, BAD_CAST"fov"));
	return (1);
}

int				set_lights(t_list *lst, t_rt *e)
{
	int i;

	i = 0;
	e->scene.nbr_light = ft_lstlen(lst);
	e->scene.lights = (t_light *)malloc(sizeof(t_light) * e->scene.nbr_light);
	if (!e->scene.lights)
		exit(ERR);
	while (lst)
	{
		e->CLIGHT = get_light((xmlNodePtr)lst->content);
		lst = lst->next;
		i++;
	}
	ft_lstfree(&lst);
	return (1);
}

int				parse_doc(t_rt *e, char *path)
{
	xmlDocPtr	doc;
	t_list		*lst;

	xmlKeepBlanksDefault(0);
	if (!(doc = getdoc(path)))
		return (-1);
	if (!doChecks(doc))
		return (0);
	lst = get_object_nodes(doc);
	create_objs(e, lst);
	ft_lstfree(&lst);
	get_nodes_by_name(xmlDocGetRootElement(doc), "camera", &lst);
	set_camera_xml(e, (xmlNodePtr)(lst->content));
	ft_lstfree(&lst);
	get_nodes_by_name(xmlDocGetRootElement(doc), "light", &lst);
	set_lights(lst, e);
	return (1);
}
