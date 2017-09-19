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

void ft_init_values(t_rt *e)
{
   e->gtk.values.width = LARGEUR;
   e->gtk.values.height = HAUTEUR;
   e->gtk.values.res = RES;
  printf("width      = {%d}\n", LARGEUR);
	printf("height     = {%d}\n", HAUTEUR);
	printf("RES        = {%d}\n", RES);
	printf("anti-alias = {%d}\n\n", ALIASING);
}

void ft_gtk_link_css(GtkWidget *window, gchar *css)
{
  GtkCssProvider *cssProvider = gtk_css_provider_new();
  gtk_css_provider_load_from_path(cssProvider, css, NULL);
  gtk_style_context_add_provider(gtk_widget_get_style_context(window),
                                 GTK_STYLE_PROVIDER(cssProvider),
                                 GTK_STYLE_PROVIDER_PRIORITY_USER);
}

void ft_gtk_start_settings(t_rt *e)
{
    gtk_init(NULL, NULL);
    ft_init_values(e);
    ft_settings(e);
    gtk_main();
}

void ft_gtk_start_launcher(t_rt *e)
{
    gtk_init(NULL, NULL);
    e->gtk.menu.window = new_window(GTK_W, GTK_H, "RT");
		e->gtk.menu.layout = gtk_layout_new(NULL, NULL);
		gtk_container_add(GTK_CONTAINER(e->gtk.menu.window), e->gtk.menu.layout);
		ft_gtk_link_css(e->gtk.menu.window, "srcs/gtk/css/style.css");
    ft_init_values(e);
		ft_gtk_launcher(e);
    gtk_widget_show_all(e->gtk.menu.window);
    gtk_main();
}

