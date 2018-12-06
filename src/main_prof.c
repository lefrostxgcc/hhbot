#include <gtk/gtk.h>
#include <hhapi.h>

#define	PROGRAM_TITLE	"HH Professional"
enum {SPACING = 10, WINDOW_WIDTH = 525, WINDOW_HEIGHT = 350};

static void on_menubar_item_test_activated();
static void on_button_search_clicked(GtkWidget *button, gpointer data);
static void show_vacancies_on_text_view(struct VacancyArray *vacancies);

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
	GtkWidget		*window_test;
	GtkWidget		*vbox;
	GtkWidget		*text_view_res;
	GtkWidget		*entry_search;
	GtkWidget		*button_search;

    window_test = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window_test), "Test");
	gtk_container_set_border_width(GTK_CONTAINER(window_test), SPACING * 2);
	gtk_window_set_default_size(GTK_WINDOW(window_test),
		WINDOW_WIDTH, WINDOW_HEIGHT);
	gtk_window_set_modal(GTK_WINDOW(window_test), TRUE);

	text_view_res = gtk_text_view_new();
	entry_search = gtk_entry_new();
	button_search = gtk_button_new_with_label("Test");

	gtk_widget_set_halign(button_search, GTK_ALIGN_START);

	vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, SPACING);
	gtk_box_pack_start(GTK_BOX(vbox), text_view_res, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), entry_search, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), button_search, FALSE, FALSE, 0);
	gtk_container_add(GTK_CONTAINER(window_test), vbox);

	gtk_widget_set_name(window_test, "test_window");

	g_signal_connect(G_OBJECT(button_search), "clicked",
						G_CALLBACK(on_button_search_clicked),
						(gpointer)entry_search);

	g_signal_connect_swapped(G_OBJECT(window_test), "destroy",
								G_CALLBACK(gtk_widget_destroy), window_test);

    gtk_widget_show_all(window_test);
}

static void on_button_search_clicked(GtkWidget *button, gpointer data)
{
	struct VacancyArray	vacancies;
	const char			*entry_text;
	char				*url;
	char				*request;

	entry_text = gtk_entry_get_text(GTK_ENTRY(data));
	url = g_strconcat("http://api.hh.ru/vacancies?text=", entry_text, NULL);

	request = hhapi_get_request(url);
	vacancies = hhapi_parse_json_items(request);

	show_vacancies_on_text_view(&vacancies);

	hhapi_free_vacancies(&vacancies);
	g_free(request);
	g_free(url);
}

static void show_vacancies_on_text_view(struct VacancyArray *vacancies)
{
	g_message("show_vacancies_on_text_view");
}
