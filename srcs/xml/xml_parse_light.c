/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_parse_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agfernan <agfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 23:32:55 by agfernan          #+#    #+#             */
/*   Updated: 2017/09/30 23:33:27 by agfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				parse_light_node(t_light *light, xmlNodePtr node)
{
	xmlChar		*val;
	xmlNodePtr	child;

	if ((val = xmlGetProp(node, BAD_CAST"intensity")))
		(*light).intensity = atof((char *)val);
	if ((child = has_child(node, "pos")))
		(*light).ray.pos = get_vec_from_node(child);
	if ((child = has_child(node, "color")))
		(*light).color = parse_color(child);
	return (1);
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
