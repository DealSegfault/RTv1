/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_get_nodes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agfernan <agfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 16:45:45 by agfernan          #+#    #+#             */
/*   Updated: 2017/09/30 22:29:25 by agfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			get_nodes_by_name(xmlNodePtr cur, char *node_name, t_list **lst)
{
	t_list	*new;

	while (cur)
	{
		if ((!xmlStrcmp(cur->name, (const xmlChar *)node_name)))
		{
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

t_vec3			get_vec_from_node(xmlNodePtr node)
{
	t_vec3 new;

	new.x = ft_atof((char *)(xmlGetProp(node, BAD_CAST"x")));
	new.y = ft_atof((char *)(xmlGetProp(node, BAD_CAST"y")));
	new.z = ft_atof((char *)(xmlGetProp(node, BAD_CAST"z")));
	return (new);
}
