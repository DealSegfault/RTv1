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



gboolean ft_gtk_setting_closed (GtkWidget *widget, GdkEvent  *event, gpointer *window)
{
	if (widget && event)
	{}
	gtk_widget_set_sensitive (GTK_WIDGET(window), 1);
	return FALSE;
}

void print_text(GtkEntry *entry, void *optional_data)
{
    //retrieve text from entry with gtk_entry_get_text()
    if (optional_data){}
    printf("Text in Entry: %s\n", gtk_entry_get_text(GTK_ENTRY(entry)));
}

GtkWidget	*ft_gtk_new_input(t_rt *e, ft_gtk_input *data)
{
	GtkWidget 			*input;

  input = gtk_entry_new();
  gtk_entry_set_max_length(GTK_ENTRY(input), data->max_size);
  gtk_entry_set_width_chars(GTK_ENTRY(input), data->max_char);
  gtk_entry_set_placeholder_text(GTK_ENTRY(input), data->placeholder);
	gtk_entry_set_text (GTK_ENTRY(input), data->deflaut_value);
	gtk_layout_put(GTK_LAYOUT(e->gtk.set.layout), input, data->pos_x, data->pos_y);
	g_signal_connect(input, "activate", G_CALLBACK(print_text), NULL);
  // g_signal_connect(gtk->window, "destroy", gtk_main_quit, NULL);
	return (input);
}

void ft_gtk_settings(t_rt *e)
{
	ft_gtk_input i_width;

	i_width.pos_x = 20;
	i_width.pos_y = 20;
	i_width.max_char = 5;
	i_width.max_size = 5;
	i_width.placeholder = "width";
	i_width.deflaut_value = "1250";
	ft_gtk_new_input(e, &i_width);
}

void btn_settings_clicked(GtkWidget *btn, t_rt *e)
{
	if (btn){}
	gtk_widget_set_sensitive (GTK_WIDGET(e->gtk.menu.window), 0);
	e->gtk.set.window = ft_gtk_new_window(600, 600, "Settings");
	ft_gtk_link_css(e->gtk.set.window, "srcs/css/style.css");
	e->gtk.set.layout = gtk_layout_new(NULL, NULL);
	gtk_container_add(GTK_CONTAINER(e->gtk.set.window), e->gtk.set.layout);
	ft_gtk_settings(e);
	gtk_widget_show_all (e->gtk.set.window);
	g_signal_connect (e->gtk.set.window, "delete-event", G_CALLBACK(ft_gtk_setting_closed), e->gtk.menu.window);
}

void ft_gtk_add_btn_settings(t_rt *e)
{
	GtkWidget 			*btn;
	int 						pos[2];
	int 						size[2];

	pos[0] = 50;
	pos[1] = 50;
	size[0] = 200;
	size[1] = 40;
	btn = ft_gtk_new_btn(e, pos, size, "Settings");
	g_signal_connect (btn, "clicked", G_CALLBACK(btn_settings_clicked), e);
}



void btn_open_scene_clicked(GtkWidget *btn, t_rt *e)
{
	GtkWidget *dialog;
	GtkWidget *win;
	gint res;
	char *filename;


	if (btn){}

	win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	// gtk_window_set_position (GTK_WINDOW(win), GTK_WIN_POS_CENTER);
	dialog = gtk_file_chooser_dialog_new ("Open File", GTK_WINDOW(win),
																				GTK_FILE_CHOOSER_ACTION_OPEN,
																				"Cancel",GTK_RESPONSE_CANCEL,
																				"Open", GTK_RESPONSE_ACCEPT,
																				NULL);

	res = gtk_dialog_run (GTK_DIALOG (dialog));
	if (res == GTK_RESPONSE_ACCEPT)
	{
	    filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
			gtk_widget_destroy (dialog);
			if (parse_filename(e, filename))
			{
				gtk_widget_destroy (e->gtk.menu.window);
				ft_start_rt(e);
			}
			g_free (filename);
	}
	else
			gtk_widget_destroy (dialog);

}

void ft_gtk_add_btn_open_scene(t_rt *e)
{
	GtkWidget 			*btn;
	int pos[2];
	int size[2];

	pos[0] = 50;
	pos[1] = 110;
	size[0] = 200;
	size[1] = 40;
	btn = ft_gtk_new_btn(e, pos, size, "Open scene");
	g_signal_connect (btn, "clicked", G_CALLBACK(btn_open_scene_clicked), e);

}

void ft_gtk_add_btn(t_rt *e)
{
	ft_gtk_add_btn_settings(e);
	ft_gtk_add_btn_open_scene(e);
}
