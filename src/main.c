#include <gtk/gtk.h>
#include <hhapi.h>

#define	PROGRAM_TITLE	"HHBot"
enum {SPACING = 10, WINDOW_WIDTH = 400, WINDOW_HEIGHT = 300};

static void on_button_test_clicked(GtkWidget *button, gpointer data);
static void on_button_parse_clicked(GtkWidget *button, gpointer data);

int main(int argc, char *argv[])
{
	GtkWidget *window, *label_json_request, *json_scrolls, *button_test;
	GtkWidget *button_parse;
	GtkWidget *vbox, *hbox;

    gtk_init (&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), PROGRAM_TITLE);
	gtk_container_set_border_width(GTK_CONTAINER (window), SPACING);
	gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);

	label_json_request = gtk_label_new(NULL);
	gtk_label_set_selectable(GTK_LABEL(label_json_request), TRUE);
	gtk_label_set_line_wrap(GTK_LABEL(label_json_request), TRUE);
	json_scrolls = gtk_scrolled_window_new(NULL, NULL);
	gtk_container_add(GTK_CONTAINER(json_scrolls), label_json_request);

	button_test = gtk_button_new_with_label("Тест");
	button_parse = gtk_button_new_with_label("Парсинг");

	vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, SPACING);
	hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, SPACING);

	gtk_box_pack_start(GTK_BOX(hbox), button_test, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox), button_parse, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), json_scrolls, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
	
	gtk_container_add(GTK_CONTAINER(window), vbox);

	g_signal_connect(G_OBJECT(button_test), "clicked",
						G_CALLBACK(on_button_test_clicked),
						(gpointer)label_json_request);

	g_signal_connect(G_OBJECT(button_parse), "clicked",
						G_CALLBACK(on_button_parse_clicked),
						(gpointer)label_json_request);

	g_signal_connect(G_OBJECT(window), "destroy",
    				  G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();

	return 0;
}

static void on_button_test_clicked(GtkWidget *button, gpointer data)
{
	gchar *json_request;

	json_request = hhapi_get_request("http://api.hh.ru/vacancies/27562280");
	gtk_label_set_text(GTK_LABEL(data), json_request);
	g_free(json_request);
}

static void on_button_parse_clicked(GtkWidget *button, gpointer data)
{
	gchar *json_request, *json_parse;

	json_request = hhapi_get_request("http://api.hh.ru/vacancies/27562280");
	json_parse = hhapi_parse_json(json_request);
	gtk_label_set_text(GTK_LABEL(data), json_parse);
	g_free(json_parse);
	g_free(json_request);
}
