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

GtkWidget *ft_gtk_new_btn(t_rt *e, int pos[], int size[], char *name)
{
	GtkWidget 			*btn;

	btn = gtk_button_new_with_label(name);
	gtk_widget_set_size_request(btn, size[0], size[1]);
	gtk_layout_put(GTK_LAYOUT(e->gtk.menu.layout), btn, pos[0], pos[1]);
	return (btn);
}

GtkWidget *ft_gtk_new_window(gint w, gint h, gchar *name)
{
	GtkWidget *win;

  win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(win), w, h);
	gtk_window_set_resizable(GTK_WINDOW(win), FALSE);
	gtk_window_set_position(GTK_WINDOW(win), GTK_WIN_POS_CENTER);
  gtk_window_set_title(GTK_WINDOW(win), name);
	return (win);
}
