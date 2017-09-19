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

void ft_gtk_link_css(GtkWidget *window, gchar *css)
{
  GtkCssProvider *cssProvider = gtk_css_provider_new();
  gtk_css_provider_load_from_path(cssProvider, css, NULL);
  gtk_style_context_add_provider(gtk_widget_get_style_context(window),
                                 GTK_STYLE_PROVIDER(cssProvider),
                                 GTK_STYLE_PROVIDER_PRIORITY_USER);
}

void ft_gtk_add_radio_filters(t_rt *e)
{
	if (e){}
  //  GtkWidget *radio1, *radio2, *box;
  //
  //  box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 2);
  //  gtk_box_set_homogeneous (GTK_BOX (box), TRUE);
  //
  //
  // radio1 = gtk_radio_button_new_with_label_from_widget (GTK_RADIO_BUTTON (radio1), "filtre 1");
  // // radio2 = gtk_radio_button_new_with_label_from_widget (GTK_RADIO_BUTTON (radio1), "filtre 2");
  //
  // gtk_box_pack_start (GTK_BOX(box), radio1, TRUE, TRUE, 2);
  // // gtk_box_pack_start (GTK_BOX(box), radio2, TRUE, TRUE, 2);
  //
  // gtk_layout_put(GTK_LAYOUT(gtk->layout), box, 100, 250);

}

void ft_gtk_start(t_rt *e, int argc, char **argv)
{
    gtk_init(&argc, &argv);

    e->gtk.menu.window = ft_gtk_new_window(GTK_W, GTK_H, "RT");
		e->gtk.menu.layout = gtk_layout_new(NULL, NULL);
		gtk_container_add(GTK_CONTAINER(e->gtk.menu.window), e->gtk.menu.layout);

		ft_gtk_link_css(e->gtk.menu.window, "srcs/css/style.css");
    // ft_gtk_add_logo(&gtk);
		ft_gtk_add_btn(e);
    gtk_widget_show_all(e->gtk.menu.window);
    gtk_main();
}
