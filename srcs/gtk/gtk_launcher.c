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

gboolean ft_close_settings(GtkWidget *widget, GdkEvent  *event, t_rt *e)
{
	if (widget && event)
		gtk_widget_set_sensitive(GTK_WIDGET(e->gtk.menu.window), 1);
	return FALSE;
}

void btn_settings_clicked(GtkWidget *btn, t_rt *e)
{
	if (btn){}
	gtk_widget_set_sensitive(GTK_WIDGET(e->gtk.menu.window), 0);
	ft_settings(e);
	g_signal_connect(e->gtk.settings.window, "delete-event", G_CALLBACK(ft_close_settings), e);

}

void btn_settings(t_rt *e)
{
	GtkWidget 			*btn;

	btn = new_btn(200, 40, "Settings");
	gtk_layout_put(GTK_LAYOUT(e->gtk.menu.layout), btn, 50, 50);	
	g_signal_connect(btn, "clicked", G_CALLBACK(btn_settings_clicked), e);
}

void open_scene_clicked(GtkWidget *btn, t_rt *e)
{
	GtkWidget *dialog;
	GtkWidget *win;
	gint res;
	char *filename;

	if (btn || e){}
	win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	dialog = gtk_file_chooser_dialog_new(	"Open File", GTK_WINDOW(win),
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

void open_scene(t_rt *e)
{
	GtkWidget 			*btn;

	btn = new_btn(200, 40, "Open scene");
	gtk_layout_put(GTK_LAYOUT(e->gtk.menu.layout), btn, 50, 110);
	g_signal_connect(btn, "clicked", G_CALLBACK(open_scene_clicked), e);
}

void ft_gtk_launcher(t_rt *e)
{
	btn_settings(e);
	open_scene(e);
}
