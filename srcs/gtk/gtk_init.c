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

void		ft_init_values(t_rt *e)
{
	e->gtk.values.width = LARGEUR;
	e->gtk.values.height = HAUTEUR;
	e->gtk.values.res = RES;
}

gboolean	hook(GtkWidget *widget, GdkEventKey *event, gpointer user_data)
{
	(void)widget;
	(void)user_data;
	if (event->keyval == 65307)
		exit(42);
	return (FALSE);
}

void		ft_gtk_start_settings(t_rt *e)
{
	gtk_init(NULL, NULL);
	e->gtk.settings.window = new_window(200, 300, "Settings");
	e->gtk.settings.layout = gtk_layout_new(NULL, NULL);
	gtk_container_add(GTK_CONTAINER(e->gtk.settings.window),
									e->gtk.settings.layout);
	ft_init_values(e);
	ft_settings(e);
	gtk_widget_show_all(e->gtk.settings.window);
	g_signal_connect(G_OBJECT(e->gtk.settings.window),
								"key_press_event", G_CALLBACK(hook), NULL);
	gtk_main();
}

void		ft_gtk_start_launcher(t_rt *e)
{
	gtk_init(NULL, NULL);
	e->gtk.menu.window = new_window(300, 200, "RT");
	e->gtk.menu.layout = gtk_layout_new(NULL, NULL);
	gtk_container_add(GTK_CONTAINER(e->gtk.menu.window), e->gtk.menu.layout);
	ft_init_values(e);
	ft_gtk_launcher(e);
	gtk_widget_show_all(e->gtk.menu.window);
	g_signal_connect(G_OBJECT(e->gtk.menu.window),
								"key_press_event", G_CALLBACK(hook), NULL);
	gtk_main();
}
