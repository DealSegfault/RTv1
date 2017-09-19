/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparigi <mparigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/02 21:26:40 by mparigi           #+#    #+#             */
/*   Updated: 2017/09/03 16:04:22 by mparigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		disp_cam(t_rt *e)
{
	mlx_string_put(INIT, WIN, 10, 10, 0, "FoV");
	mlx_string_put(INIT, WIN, 50, 10, 0, ft_itoa(e->scene.cam.fov));
	mlx_string_put(INIT, WIN, 10, 30, 0, "Rotation X");
	mlx_string_put(INIT, WIN, 150, 30, 0, ft_itoa(e->scene.cam.rotx));
	mlx_string_put(INIT, WIN, 10, 50, 0, "Rotation Y");
	mlx_string_put(INIT, WIN, 150, 50, 0, ft_itoa(e->scene.cam.roty));
	mlx_string_put(INIT, WIN, 10, 70, 0, "Rotation Z");
	mlx_string_put(INIT, WIN, 150, 70, 0, ft_itoa(e->scene.cam.rotz));
	mlx_string_put(INIT, WIN, 10, 90, 0, "Position X");
	mlx_string_put(INIT, WIN, 150, 90, 0, ft_itoa(CPOS.x));
	mlx_string_put(INIT, WIN, 10, 110, 0, "Position Y");
	mlx_string_put(INIT, WIN, 150, 110, 0, ft_itoa(CPOS.y));
	mlx_string_put(INIT, WIN, 10, 130, 0, "Position Z");
	mlx_string_put(INIT, WIN, 150, 130, 0, ft_itoa(CPOS.z));
}
