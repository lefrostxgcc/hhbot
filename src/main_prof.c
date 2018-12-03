#include <gtk/gtk.h>

#define	PROGRAM_TITLE	"HH Professional"
enum {SPACING = 10, WINDOW_WIDTH = 500, WINDOW_HEIGHT = 400};

int main(int argc, char *argv[])
{
	GtkWidget		*window;
	GtkCssProvider	*css_provider;

    gtk_init (&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), PROGRAM_TITLE);
	gtk_container_set_border_width(GTK_CONTAINER(window), SPACING);
	gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);

	css_provider = gtk_css_provider_new();
	gtk_css_provider_load_from_resource(css_provider, "/hh_prof.css");
	gtk_style_context_add_provider_for_screen(
		gdk_display_get_default_screen(gdk_display_get_default()),
		GTK_STYLE_PROVIDER(css_provider),
		GTK_STYLE_PROVIDER_PRIORITY_USER);

	g_signal_connect(G_OBJECT(window), "destroy",
						G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();

	return 0;
}
