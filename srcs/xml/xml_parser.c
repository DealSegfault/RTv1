/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparigi <mparigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 11:35:38 by agfernan          #+#    #+#             */
/*   Updated: 2017/10/04 18:34:22 by mparigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

xmlNodePtr		has_child(xmlNodePtr a_node, char *attr)
{
	xmlChar		*cast;
	xmlNodePtr	cur;

	cur = NULL;
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

static int		is_file(char *path)
{
	int		fd;
	int		size;

	if (!path)
		return (-1);
	size = ft_strlen(path) - ft_strlen(EXTENSION);
	if (!ft_strcmp(EXTENSION, path + size))
		if ((fd = open(path, O_RDONLY)) != -1)
			return (fd);
	return (-1);
}

int				parse_doc2(t_rt *e, char *path)
{
	xmlDocPtr	doc;
	t_list		*lst;
	xmlNodePtr	skybox;
	xmlNodePtr	root;

	xmlKeepBlanksDefault(0);
	if (!(doc = getdoc(path)) || !do_checks(doc))
		return (0);
	root = xmlDocGetRootElement(doc);
	parse_ambient(e, root);
	if ((skybox = has_child(root, "skybox")))
		parse_skybox(e, skybox);
	lst = get_object_nodes(doc);
	create_objs(e, lst);
	ft_lstfree(&lst);
	get_nodes_by_name(root, "camera", &lst);
	if (!lst)
		camera_create(e);
	else
		set_camera_xml(e, (xmlNodePtr)(lst->content));
	ft_lstfree(&lst);
	get_nodes_by_name(root, "light", &lst);
	set_lights(lst, e);
	return (1);
}

int				parse_doc(t_rt *e)
{
	int fd;

	if (HAUTEUR > 5000 || LARGEUR > 5000)
		exit(42);
	if ((fd = is_file(SFILE)) > -1)
		if (parse_doc2(e, SFILE) > 0)
		{
			create_complex(e);
			return (1);
		}
	return (0);
}

int				parse_args(char **argv, int argc, t_rt *e)
{
	int		i;

	i = 1;
	while (i < argc)
	{
		if (!ft_strcmp("--help", argv[i]))
		{
			display_args();
			return (0);
		}
		else if (!ft_strcmp("-w", argv[i]))
			i + 1 < argc ? e->file.larg = ft_atoi(argv[i + 1]) : 0;
		else if (!ft_strcmp("-h", argv[i]))
			i + 1 < argc ? e->file.haut = ft_atoi(argv[i + 1]) : 0;
		else if (!ft_strcmp("-s", argv[i]))
			i + 1 < argc ? SFILE = ft_strdup(argv[i + 1]) : 0;
		else
			return (0);
		i += 2;
	}
	return (parse_doc(e));
}
