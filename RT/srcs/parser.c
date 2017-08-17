/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocojeda- <ocojeda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 00:28:28 by mhalit            #+#    #+#             */
/*   Updated: 2017/08/17 16:58:47 by ocojeda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

int			create_type(char *type, t_rt *env)
{
	if (!ft_strcmp("sphere:", type))
		return (create_obj(SPHERE, env));
	if (!ft_strcmp("plane:", type))
		return (create_obj(PLANE, env));
	if (!ft_strcmp("light:", type))
		return (create_light(env));
	if (!ft_strcmp("camera:", type))
		return (camera_create(env));
	return (0);
}

void		store_type_or_data(char *line, t_rt *env)
{
	char	**tab;

	tab = ft_split_whitespace(line);
	if (tab && tab[0] && create_type(tab[0], env))
		env->scene.last = ft_strdup(tab[0]);
	if (tab && tab[0] && tab[1])
		set_last(env, tab);
}

static int	is_file(char *path)
{
	char	*tmp;
	int		fd;

	tmp = ft_strchr(path, '.');
	if (tmp && !ft_strcmp(EXTENSION, tmp))
		if ((fd = open(path, O_RDONLY)) != -1)
			return (1);
	return (0);
}

int			parse_obj(char *path, t_rt *env)
{
	int		fd;
	char	*line;

	if (!(fd = open(path, O_RDONLY)))
		return (0);
	while (get_next_line(fd, &line))
	{
		if (line && line[0] != '*')
			store_type_or_data(line, env);
	}
	env->scene.nbr_tot = env->scene.nbr_obj + env->scene.nbr_light;
	return (1);
}

int			parse_args(char **argv, int argc, t_rt *env)
{
	int		i;

	i = 0;
	while (i < argc)
	{
		if (!ft_strcmp("--help", argv[i]))
		{
			display_args();
			return (0);
		}
		else if (!ft_strcmp("-w", argv[i]))
			i + 1 < argc ? env->file.larg = ft_atoi(argv[i + 1]) : 0;
		else if (!ft_strcmp("-h", argv[i]))
			i + 1 < argc ? env->file.haut = ft_atoi(argv[i + 1]) : 0;
		else if (!ft_strcmp("-s", argv[i]))
			i + 1 < argc ? SFILE = ft_strdup(argv[i + 1]) : 0;
		else if (!ft_strcmp("-a", argv[i]))
			i + 1 < argc ? SS = 2 : 0;
		i++;
	}
	if (is_file(SFILE))
		if (parse_obj(SFILE, env))
			return (1);
	return (0);
}
