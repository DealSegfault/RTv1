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

void ft_add_w(GtkEntry *entry, t_rt *e)
{
		int val;

		val = ft_atoi(gtk_entry_get_text(GTK_ENTRY(entry)));
		if (val > 2)
				e->gtk.values.width = val;
}

void ft_add_h(GtkEntry *entry, t_rt *e)
{
		int val;

		val = ft_atoi(gtk_entry_get_text(GTK_ENTRY(entry)));
		if (val > 2)
				e->gtk.values.height = val;
}

void ft_add_res(GtkEntry *entry, t_rt *e)
{
		int val;

		val = ft_atoi(gtk_entry_get_text(GTK_ENTRY(entry)));
		if (val >= 1)
			e->gtk.values.res = val;
}

void ft_add_anti(GObject *sw, GParamSpec *ps, t_rt *e)
{
	if (sw && ps && e) {}

	if (gtk_switch_get_active(GTK_SWITCH(sw)))
		ALIASING = 2;
  	else
		ALIASING = 1;
}

void ft_add_win_size(t_rt *e)
{
	t_gtk_input input;
	GtkWidget 	*width;
	GtkWidget 	*height;

	input.max_char = 5;
	input.max_size = 5;
	input.placeholder = "width";
	input.deflaut_value = ft_itoa(LARGEUR);
	width = new_input(&input);
	input.placeholder = "height";
	input.deflaut_value = ft_itoa(HAUTEUR);
	height = new_input(&input);

	gtk_layout_put(GTK_LAYOUT(e->gtk.settings.layout), width, 20, 40);
	gtk_layout_put(GTK_LAYOUT(e->gtk.settings.layout), height, 80, 40);
	g_signal_connect(width, "activate", G_CALLBACK(ft_add_w), e);
	g_signal_connect(height, "activate", G_CALLBACK(ft_add_h), e);
}

void ft_add_resolution(t_rt *e)
{
	t_gtk_input input;
	GtkWidget 	*res;

	input.max_char = 3;
	input.max_size = 3;
	input.placeholder = "RES";
	input.deflaut_value = ft_itoa(RES);
	res = new_input(&input);
	gtk_layout_put(GTK_LAYOUT(e->gtk.settings.layout), res, 20, 110);
	g_signal_connect(res, "activate", G_CALLBACK(ft_add_res), e);
}

void ft_add_antialiasing(t_rt *e)
{
	GtkWidget *sw;

	sw = gtk_switch_new();
	if (ALIASING == 1)
		gtk_switch_set_active(GTK_SWITCH(sw), FALSE);
	else
		gtk_switch_set_active(GTK_SWITCH(sw), TRUE);
	g_signal_connect(GTK_SWITCH(sw), "notify::active", G_CALLBACK(ft_add_anti), e);
	gtk_layout_put(GTK_LAYOUT(e->gtk.settings.layout), sw, 20, 180);
	gtk_widget_show_all (e->gtk.settings.window);
}

void ft_update(GtkButton *btn, t_rt *e)
{
	if (btn){}
	gtk_widget_destroy(e->gtk.settings.window);	

	LARGEUR = e->gtk.values.width;
	HAUTEUR = e->gtk.values.height;
	RES = e->gtk.values.res;

	printf("width      = {%d}\n", LARGEUR);
	printf("height     = {%d}\n", HAUTEUR);
	printf("RES        = {%d}\n", RES);
	printf("anti-alias = {%d}\n\n", ALIASING);

	if (e->started == 1)
		ft_start_rt(e);
	else
		gtk_widget_set_sensitive(GTK_WIDGET(e->gtk.menu.window), 1);
}

void ft_btn_update(t_rt *e)
{
	GtkWidget 			*btn;

	btn = new_btn(100, 40, "UPDATE");
	gtk_layout_put(GTK_LAYOUT(e->gtk.settings.layout), btn, 50, 250);
	g_signal_connect (btn, "clicked", G_CALLBACK(ft_update), e);
}

void ft_display_settings(t_rt *e)
{
	gtk_layout_put(GTK_LAYOUT(e->gtk.settings.layout), new_txt("Screen size"), 20, 20);
	gtk_widget_show_all (e->gtk.settings.window);
	ft_add_win_size(e);
	gtk_layout_put(GTK_LAYOUT(e->gtk.settings.layout), new_txt("Resolution"), 20, 90);
	gtk_widget_show_all (e->gtk.settings.window);	
	ft_add_resolution(e);
  	gtk_layout_put(GTK_LAYOUT(e->gtk.settings.layout), new_txt("anti-aliasing"), 20, 160);
	gtk_widget_show_all (e->gtk.settings.window);	
	ft_add_antialiasing(e);
	ft_btn_update(e);
}

void ft_settings(t_rt *e)
{
	e->gtk.settings.window = new_window(200, 300, "Settings");
	e->gtk.settings.layout = gtk_layout_new(NULL, NULL);
	ft_gtk_link_css(e->gtk.settings.window, "srcs/gtk/css/style.css");
	gtk_container_add(GTK_CONTAINER(e->gtk.settings.window), e->gtk.settings.layout);
	ft_display_settings(e);
	gtk_widget_show_all (e->gtk.settings.window);
}
