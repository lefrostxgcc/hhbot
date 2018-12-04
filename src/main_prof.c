#include <gtk/gtk.h>

#define	PROGRAM_TITLE	"HH Professional"
enum {SPACING = 10, WINDOW_WIDTH = 525, WINDOW_HEIGHT = 350};

static void on_menubar_item_test_activated();

int main(int argc, char *argv[])
{
	GtkWidget		*window;
	GtkCssProvider	*css_provider;
	GtkWidget		*menu;
	GtkWidget		*menu_resume;
	GtkWidget		*menu_root_vacancy;
	GtkWidget		*menu_root_resume;
	GtkWidget		*menu_root_test;
	GtkWidget		*menu_resume_list;
	GtkWidget		*menu_resume_create;
	GtkWidget		*menu_resume_root_create;
	GtkWidget		*menu_resume_create_new;
	GtkWidget		*vbox;

    gtk_init (&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), PROGRAM_TITLE);
	gtk_container_set_border_width(GTK_CONTAINER(window), 0);
	gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);

	menu = gtk_menu_bar_new();
	menu_resume = gtk_menu_new();
	menu_resume_create = gtk_menu_new();
	menu_root_vacancy = gtk_menu_item_new_with_label("Вакансии");
	menu_root_resume = gtk_menu_item_new_with_label("Резюме");
	menu_resume_list = gtk_menu_item_new_with_label("Список резюме");
	menu_resume_root_create = gtk_menu_item_new_with_label("Создать");
	menu_resume_create_new = gtk_menu_item_new_with_label("Новое");
	menu_root_test = gtk_menu_item_new_with_label("Test");

	gtk_menu_shell_append(GTK_MENU_SHELL(menu_resume), menu_resume_list);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_resume), menu_resume_root_create);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_resume_create),
		menu_resume_create_new);

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_root_resume), menu_resume);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_resume_root_create),
		menu_resume_create);

	gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_root_vacancy);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_root_resume);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_root_test);

	g_signal_connect(G_OBJECT(menu_root_test), "activate",
						G_CALLBACK(on_menubar_item_test_activated), NULL);

	vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start(GTK_BOX(vbox), menu, FALSE, FALSE, 0);
	gtk_container_add(GTK_CONTAINER(window), vbox);

	css_provider = gtk_css_provider_new();
	gtk_css_provider_load_from_resource(css_provider, "/hh_prof.css");
	gtk_style_context_add_provider_for_screen(
		gdk_display_get_default_screen(gdk_display_get_default()),
		GTK_STYLE_PROVIDER(css_provider),
		GTK_STYLE_PROVIDER_PRIORITY_USER);

	gtk_widget_set_name(menu, "hh_menubar");

	g_signal_connect(G_OBJECT(window), "destroy",
						G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();

	return 0;
}

static void on_menubar_item_test_activated()
{
	g_message("Test");
}
