/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 17:35:26 by mhalit            #+#    #+#             */
/*   Updated: 2017/10/01 17:35:35 by mhalit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float			cartoon_color(float color)
{
	if (color < 15)
		color = 30;
	else if (color < 75)
		color = 75;
	else if (color < 120)
		color = 120;
	else if (color < 220)
		color = 220;
	else if (color < 255)
		color = 255;
	return (color);
}

t_color			fl_cartoon(t_color color)
{
	color.r = cartoon_color(color.r);
	color.g = cartoon_color(color.g);
	color.b = cartoon_color(color.b);
	return (color);
}
