/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_parse_negs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agfernan <agfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 23:34:39 by agfernan          #+#    #+#             */
/*   Updated: 2017/10/01 17:42:39 by agfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			init_plimit(t_obj *plimit, t_color c, xmlNodePtr node)
{
	t_vec3	dir;

	dir = get_vec_from_node(has_child(node, "dir"));
	(*plimit).is_init = -1;
	(*plimit).type = PLANE;
	(*plimit).r = dir.x;
	(*plimit).color = c;
	(*plimit).dir = vec_new3(0, 0, 0);
	(*plimit).k = dir.x;
	(*plimit).mat = create_matiere();
	(*plimit).plimit_active = 0;
	(*plimit).nbr_limit = 0;
	(*plimit).t = -1;
	(*plimit).plimit = NULL;
}

t_list			*get_negatives(xmlNodePtr node)
{
	xmlNodePtr	tmp;
	t_list		*lst;

	lst = NULL;
	tmp = node;
	lst = ft_lstnew(node, sizeof(*node));
	tmp = tmp->next;
	while (tmp)
	{
		if (!xmlStrcmp(tmp->name, BAD_CAST"negatif"))
			ft_lstpush(&lst, ft_lstnew(tmp, sizeof(tmp)));
		tmp = tmp->next;
	}
	return (lst);
}

t_vec3			get_vec_neg(xmlNodePtr children)
{
	t_vec3 new;

	new.x = ft_atoi((char *)(xmlGetProp(children, BAD_CAST"x")));
	new.y = ft_atoi((char *)(xmlGetProp(children, BAD_CAST"y")));
	new.z = ft_atoi((char *)(xmlGetProp(children, BAD_CAST"z")));
	return (new);
}

int				parse_negatives(t_obj *obj, xmlNodePtr node)
{
	xmlNodePtr	ch;
	int			i;
	t_list		*lst;

	i = 0;
	lst = get_negatives(node);
	(*obj).nbr_limit = ft_lstlen(lst) + 1;
	if ((*obj).nbr_limit > 0)
		(*obj).plimit = (t_obj *)malloc(sizeof(t_obj) * (*obj).nbr_limit);
	while (lst)
	{
		init_plimit(&((*obj).plimit[i]), (*obj).color, node);
		ch = has_child((xmlNodePtr)lst->content, "pos");
		(*obj).plimit[i].pos = (!ch) ? (*obj).pos : get_vec_from_node(ch);
		if ((ch = has_child((xmlNodePtr)lst->content, "dir")))
		{
			(*obj).plimit[i].normal = get_vec_neg(ch);
			(*obj).plimit[i].vector = get_vec_neg(ch);
		}
		i++;
		lst = lst->next;
	}
	(*obj).plimit_active = 1;
	ft_lstfree(&lst);
	return (1);
}
