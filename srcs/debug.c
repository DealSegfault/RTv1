/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparigi <mparigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/02 21:26:40 by mparigi           #+#    #+#             */
/*   Updated: 2017/10/01 19:33:26 by mparigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	disp_name(t_rt *e, int color)
{
	char	*tmp;
	int		i;

	i = -1;
	while (++i < e->scene.nbr_obj)
	{
		if (e->scene.obj[i].is_disp)
		{
			tmp = ft_itoa(e->scene.obj[i].type);
			mlx_string_put(INIT, WIN, e->scene.obj[i].last_pos.x * RES,
				e->scene.obj[i].last_pos.y * RES, color, tmp);
			e->scene.obj[i].is_disp = 0;
		}
	}
	free(tmp);
}

void	disp_cam(t_rt *e, int color)
{
	char	*tmp;

	mlx_string_put(INIT, WIN, 10, 10, color, "FoV");
	mlx_string_put(INIT, WIN, 50, 10, color, (tmp = ft_itoa(CCAM.fov)));
	free(tmp);
	mlx_string_put(INIT, WIN, 10, 30, color, "Rotation X");
	mlx_string_put(INIT, WIN, 150, 30, color, (tmp = ft_itoa(CCAM.rot.x)));
	free(tmp);
	mlx_string_put(INIT, WIN, 10, 50, color, "Rotation Y");
	mlx_string_put(INIT, WIN, 150, 50, color, (tmp = ft_itoa(CCAM.rot.y)));
	free(tmp);
	mlx_string_put(INIT, WIN, 10, 70, color, "Rotation Z");
	mlx_string_put(INIT, WIN, 150, 70, color, (tmp = ft_itoa(CCAM.rot.z)));
	free(tmp);
	mlx_string_put(INIT, WIN, 10, 90, color, "Position X");
	mlx_string_put(INIT, WIN, 150, 90, color, (tmp = ft_itoa(CCAM.pos.x)));
	free(tmp);
	mlx_string_put(INIT, WIN, 10, 110, color, "Position Y");
	mlx_string_put(INIT, WIN, 150, 110, color, (tmp = ft_itoa(CCAM.pos.y)));
	free(tmp);
	mlx_string_put(INIT, WIN, 10, 130, color, "Position Z");
	mlx_string_put(INIT, WIN, 150, 130, color, (tmp = ft_itoa(CCAM.pos.z)));
	mlx_string_put(INIT, WIN, 10, 150, color, "Resolution");
	mlx_string_put(INIT, WIN, 150, 150, color, (tmp = ft_itoa(RES)));
	free(tmp);
}
