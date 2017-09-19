/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agfernan <agfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 00:28:28 by mhalit            #+#    #+#             */
/*   Updated: 2017/09/19 05:38:33 by agfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			create_type(char *type, t_rt *e)
{
	if (!ft_strcmp("sphere:", type))
		return (create_obj(SPHERE, e));
	if (!ft_strcmp("plane:", type))
		return (create_obj(PLANE, e));
	if (!ft_strcmp("light:", type))
		return (create_light(e));
	if (!ft_strcmp("camera:", type))
		return (camera_create(e));
	return (0);
}

void		store_type_or_data(char *line, t_rt *e)
{
	char	**tab;

	tab = ft_split_whitespace(line);
	if (tab && tab[0] && create_type(tab[0], e))
		e->scene.last = ft_strdup(tab[0]);
	if (tab && tab[0] && tab[1])
		set_last(e, tab);
}

static int	is_file(char *path)
{
	int		fd;
	int		size;

	size = ft_strlen(path) - ft_strlen(EXTENSION);
	if (!ft_strcmp(EXTENSION, path + size))
		if ((fd = open(path, O_RDONLY)) != -1)
		{
			close(fd);
			return (1);
		}
	return (-1);
}

int			parse_obj(t_rt *e, int fd)
{
	char	*line;

	while (get_next_line(fd, &line))
	{
		if (line && line[0] != '*')
			store_type_or_data(line, e);
	}
	e->scene.nbr_tot = e->scene.nbr_obj + e->scene.nbr_light;
	if (e->scene.nbr_obj >= MAXOBJ || e->scene.nbr_light >= MAXLIGHT)
		return (0);
	return (1);
}

int			parse_args(char **argv, int argc, t_rt *e)
{
	int		i;
	int		fd;

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
		else if (!ft_strcmp("-a", argv[i]))
		 	e->scene.supersampling = 2;
		else 
			return (0);
		i += 2;
	}
	if ((fd = is_file(SFILE)) > -1)

		if (parse_doc(e, SFILE))
			return (1);
	return (0);
}
