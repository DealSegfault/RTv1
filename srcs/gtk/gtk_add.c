/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldenblyd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 22:49:45 by ldenblyd          #+#    #+#             */
/*   Updated: 2017/08/29 05:05:52 by ldenblyd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_add_w(GtkEntry *entry, t_rt *e)
{
	int val;

	val = ft_atoi(gtk_entry_get_text(GTK_ENTRY(entry)));
	if (val > 2)
		e->gtk.values.width = val;
}

void	ft_add_h(GtkEntry *entry, t_rt *e)
{
	int val;

	val = ft_atoi(gtk_entry_get_text(GTK_ENTRY(entry)));
	if (val > 2)
		e->gtk.values.height = val;
}

void	ft_add_res(GtkEntry *entry, t_rt *e)
{
	int val;

	val = ft_atoi(gtk_entry_get_text(GTK_ENTRY(entry)));
	if (val >= 1)
		e->gtk.values.res = val;
}

void	ft_add_anti(GObject *sw, GParamSpec *ps, t_rt *e)
{
	(void)ps;
	if (gtk_switch_get_active(GTK_SWITCH(sw)))
		ALIASING = 2;
	else
		ALIASING = 1;
}
