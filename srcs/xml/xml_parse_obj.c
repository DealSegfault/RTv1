/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_parse_obj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agfernan <agfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 23:28:31 by agfernan          #+#    #+#             */
/*   Updated: 2017/10/02 12:54:47 by agfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_obj			create_obj_xml(int type, int i)
{
	t_obj new;

	new.is_init = 1;
	new.is_disp = 0;
	new.type = type;
	new.color = c_color(0, 0, 0);
	new.pos = vec_new3(0, 0, 0);
	new.last_pos = (t_vec2){0, 0};
	new.dir = vec_new3(0, 0, 0);
	new.k = tan(10 * DEG2RAD / 2);
	new.r = 0;
	new.t = -1;
	new.mat = create_matiere();
	new.vector = vec_new3(0, 0, 0);
	new.normal = vec_new3(0, 0, 0);
	new.plimit_active = 0;
	new.id = i;
	new.plimit_valid = 0;
	new.nbr_limit = 0;
	new.plimit = NULL;
	return (new);
}

int				set_attrs(t_obj *obj, xmlNodePtr node)
{
	xmlChar		*val;

	if ((val = xmlGetProp(node, BAD_CAST"radius")))
		(*obj).r = ft_atof((char *)val);
	if ((val = xmlGetProp(node, BAD_CAST"angle")))
		(*obj).k = tan(ft_atof((char*)val) * DEG2RAD / 2);
	if ((val = xmlGetProp(node, BAD_CAST"reflection")))
		(*obj).mat.reflex = ft_atof((char *)val);
	if ((val = xmlGetProp(node, BAD_CAST"refraction")))
		(*obj).mat.refract = ft_atof((char *)val);
	if ((val = xmlGetProp(node, BAD_CAST"diffuse")))
		(*obj).mat.diff = ft_atof((char *)val);
	if ((val = xmlGetProp(node, BAD_CAST"specular")))
		(*obj).mat.spec = ft_atof((char *)val);
	if ((val = xmlGetProp(node, BAD_CAST"sin")))
		(*obj).mat.sin = ft_atoi((char *)val) ? 1 : 0;
	return (1);
}

int				parse_obj_node(t_obj *obj, xmlNodePtr node, t_rt *e)
{
	xmlNodePtr	child;

	set_attrs(obj, node);
	if ((child = has_child(node, "pos")))
		(*obj).pos = get_vec_from_node(child);
	if ((child = has_child(node, "dir")))
		(*obj).dir = get_vec_from_node(child);
	if ((child = has_child(node, "normal")))
		(*obj).vector = vec_norme3(get_vec_from_node(child));
	if ((child = has_child(node, "vector")))
		(*obj).vector = vec_norme3(get_vec_from_node(child));
	if ((child = has_child(node, "texture")))
		parse_texture(obj, child, e);
	if ((child = has_child(node, "color")))
		(*obj).color = parse_color(child);
	if ((child = has_child(node, "checker")))
		(*obj).mat.checker = parse_checker(child);
	if ((child = has_child(node, "negatif")))
		parse_negatives(obj, child);
	return (1);
}

t_obj			get_obj(xmlNodePtr node, t_rt *e, int i)
{
	t_obj new;

	if (!xmlStrcmp(node->name, BAD_CAST"sphere"))
		new = create_obj_xml(SPHERE, i);
	if (!xmlStrcmp(node->name, BAD_CAST"plane"))
		new = create_obj_xml(PLANE, i);
	if (!xmlStrcmp(node->name, BAD_CAST"cone"))
		new = create_obj_xml(CONE, i);
	if (!xmlStrcmp(node->name, BAD_CAST"cylindre"))
		new = create_obj_xml(CYLINDER, i);
	if (!xmlStrcmp(node->name, BAD_CAST"mickey"))
		new = create_obj_xml(MICKEY, i);
	if (!xmlStrcmp(node->name, BAD_CAST"dick"))
		new = create_obj_xml(DICK, i);
	parse_obj_node(&new, node, e);
	return (new);
}

int				create_objs(t_rt *e, t_list *lst)
{
	int i;

	i = 0;
	e->scene.nbr_obj = ft_lstlen(lst);
	if (!e->scene.nbr_obj)
		return (0);
	e->scene.obj = (t_obj *)malloc(sizeof(t_obj) * e->scene.nbr_obj);
	if (!e->scene.obj)
		exit(ERR);
	while (lst)
	{
		e->COBJ = get_obj((xmlNodePtr)lst->content, e, i);
		lst = lst->next;
		i++;
	}
	ft_lstfree(&lst);
	return (1);
}
