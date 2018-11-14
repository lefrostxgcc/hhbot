#include <gtk/gtk.h>
#include <hhapi.h>

#define	PROGRAM_TITLE	"HHBot"
enum {SPACING = 10, WINDOW_WIDTH = 400, WINDOW_HEIGHT = 300};

static void on_button_test_clicked(GtkWidget *button, gpointer data);

static GtkTextBuffer *json_text_buffer;

int main(int argc, char *argv[])
{
	GtkWidget *window, *json_text_view, *json_scrolls, *button_test;
	GtkWidget *vbox, *hbox;

    gtk_init (&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), PROGRAM_TITLE);
	gtk_container_set_border_width(GTK_CONTAINER (window), SPACING);
	gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);

	json_text_view = gtk_text_view_new();
	json_text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(json_text_view));
	json_scrolls = gtk_scrolled_window_new(NULL, NULL);
	gtk_container_add(GTK_CONTAINER(json_scrolls), json_text_view);

	button_test = gtk_button_new_with_label("Тест");

	vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, SPACING);
	hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, SPACING);

	gtk_box_pack_start(GTK_BOX(hbox), button_test, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), json_scrolls, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
	
	gtk_container_add(GTK_CONTAINER(window), vbox);

	g_signal_connect(G_OBJECT(button_test), "clicked",
						G_CALLBACK(on_button_test_clicked), NULL);

	g_signal_connect(G_OBJECT(window), "destroy",
    				  G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();

	return 0;
}

static void on_button_test_clicked(GtkWidget *button, gpointer data)
{
}
