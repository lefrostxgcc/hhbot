#include <gtk/gtk.h>
#include <hhapi.h>

#define	PROGRAM_TITLE	"HHBot"
enum {SPACING = 10, WINDOW_WIDTH = 500, WINDOW_HEIGHT = 400};
const gchar *headers[] = {
	"ID", "Name", "Salary Min", "Salary Max", "Employer", "Address", "Info"
};

static void setup_tree_view(GtkWidget *tree_view);
static GtkListStore *store;

int main(int argc, char *argv[])
{
	GtkWidget *window, *treeview_vacancies, *entry_search, *button_search;
	GtkWidget *scrolled_win, *vbox, *hbox;

    gtk_init (&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), PROGRAM_TITLE);
	gtk_container_set_border_width(GTK_CONTAINER(window), SPACING);
	gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);

	treeview_vacancies = gtk_tree_view_new();
	entry_search = gtk_entry_new();
	button_search = gtk_button_new_with_label("Search");

	setup_tree_view(treeview_vacancies);

	store = gtk_list_store_new(sizeof(headers)/sizeof(headers[0]),
		G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
		G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

	gtk_tree_view_set_model(GTK_TREE_VIEW(treeview_vacancies),
		GTK_TREE_MODEL(store));
	g_object_unref(store);

	scrolled_win = gtk_scrolled_window_new(NULL, NULL);
	gtk_container_add(GTK_CONTAINER(scrolled_win), treeview_vacancies);

	vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, SPACING);
	hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, SPACING);

	gtk_box_pack_start(GTK_BOX(hbox), entry_search, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(hbox), button_search, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), scrolled_win, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
	
	gtk_container_add(GTK_CONTAINER(window), vbox);

	g_signal_connect(G_OBJECT(window), "destroy",
    				  G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();

	return 0;
}

static void setup_tree_view(GtkWidget *tree_view)
{
	int i;
	GtkTreeViewColumn *column;
	GtkCellRenderer *render;

	for (i = 0; i < sizeof(headers)/sizeof(headers[0]); i++)
	{
		render = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes(headers[i],
			render, "text", i, NULL);
		gtk_tree_view_column_set_resizable(column, TRUE);
		gtk_tree_view_column_set_min_width(column, 20);
		gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
	}
}

/*"http://api.hh.ru/vacancies?text=Программист"*/
