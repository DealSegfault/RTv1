/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_parse_nodes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparigi <mparigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 23:26:51 by agfernan          #+#    #+#             */
/*   Updated: 2017/10/02 00:23:25 by mparigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color			parse_color(xmlNodePtr node)
{
	t_color color;

	color = c_color(
		ft_atoi((char *)xmlGetProp(node, BAD_CAST"r")),
		ft_atoi((char *)xmlGetProp(node, BAD_CAST"g")),
		ft_atoi((char *)xmlGetProp(node, BAD_CAST"b")));
	return (color);
}

int				parse_texture(t_obj *obj, xmlNodePtr node, t_rt *e)
{
	xmlChar		*val;

	if ((val = xmlGetProp(node, BAD_CAST"src")))
	{
		if (((*obj).mat.tex.ptr = mlx_xpm_file_to_image(INIT, (char*)val,
			&(*obj).mat.tex.width, &(*obj).mat.tex.height)))
		{
			if (!((*obj).mat.tex.data = mlx_get_data_addr((*obj).mat.tex.ptr,
				&(*obj).mat.tex.bpp, &(*obj).mat.tex.sizl,
				&(*obj).mat.tex.endian)))
				ft_putendl("the texture can't be loaded");
			else
				(*obj).mat.tex.is_init = 1;
		}
		else
			ft_putendl("the texture can't be loaded");
	}
	return (1);
}

t_checker		parse_checker(xmlNodePtr node)
{
	t_checker	check;
	xmlNodePtr	child;

	child = has_child(node, "color");
	check.c1 = parse_color(child);
	child = child->next;
	check.c2 = parse_color(child);
	check.l = ft_atof((char*)xmlGetProp(node, BAD_CAST"length"));
	return (check);
}

int				set_camera_xml(t_rt *e, xmlNodePtr cam_node)
{
	xmlNodePtr	child;
	xmlChar		*val;

	camera_create(e);
	if ((child = has_child(cam_node, "pos")))
	{
		CCAM.pos = get_vec_from_node(child);
		CCAM.tmp_pos = CCAM.pos;
	}
	if ((child = has_child(cam_node, "dir")))
	{
		CCAM.rot = get_vec_from_node(child);
		CCAM.tmp_rot = CCAM.rot;
	}
	if ((val = xmlGetProp(cam_node, BAD_CAST"fov")))
		CCAM.fov = ft_atoi((char*)val);
	return (1);
}
