/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_skibox.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 05:00:33 by mhalit            #+#    #+#             */
/*   Updated: 2017/10/02 05:00:41 by mhalit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	parse_skybox(t_rt *e, xmlNodePtr node)
{
	if ((e->scene.skybox.ptr = mlx_xpm_file_to_image(INIT, (char*)xmlGetProp(node, BAD_CAST"src"), &e->scene.skybox.width, &e->scene.skybox.height)))
	{
		if (!(e->scene.skybox.data = mlx_get_data_addr(e->scene.skybox.ptr,
			&e->scene.skybox.bpp, &e->scene.skybox.sizl,
			&e->scene.skybox.endian)))
			ft_putstr("skybox can't be loaded");
		else
			e->scene.skybox.is_init = 1;
	}
	else
		ft_putstr("skybox can't be loaded");
}
