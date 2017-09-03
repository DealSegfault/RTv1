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

void	ft_putstr(char const *s)
{
	int	i;

	i = 0;
	while (s[i])
		write(1, &s[i++], 1);
}

void ft_gtk_link_css(GtkWidget *window, gchar *css)
{
  GtkCssProvider *cssProvider = gtk_css_provider_new();
  gtk_css_provider_load_from_path(cssProvider, css, NULL);
  gtk_style_context_add_provider(gtk_widget_get_style_context(window),
                                 GTK_STYLE_PROVIDER(cssProvider),
                                 GTK_STYLE_PROVIDER_PRIORITY_USER);
}

void ft_gtk_start(t_rt *e)
{
    gtk_init(NULL, NULL);
    e->gtk.menu.window = ft_gtk_new_window(GTK_W, GTK_H, "RT");
		e->gtk.menu.layout = gtk_layout_new(NULL, NULL);
		gtk_container_add(GTK_CONTAINER(e->gtk.menu.window), e->gtk.menu.layout);

		ft_gtk_link_css(e->gtk.menu.window, "srcs/css/style.css");
    // ft_gtk_add_logo(&gtk);
		ft_gtk_add_btn(e);
    gtk_widget_show_all(e->gtk.menu.window);
    gtk_main();
}
