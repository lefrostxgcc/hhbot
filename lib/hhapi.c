#include <libsoup/soup.h>
#include <json-glib/json-glib.h>
#include "hhapi.h"

static char *hhapi_parse_vacancy(JsonObject *vacancy_object);
static const char *hhapi_parse_items_array(JsonArray *items_array);
static const char *hhapi_parse_salary(JsonObject *salary_object);
static guint64 hhapi_parse_int_member(JsonObject *object, const char *member);
static const char *hhapi_parse_string_member(JsonObject *object, const char *member);

const char *hhapi_get_request(const char *url)
{
	const char *responce;
	SoupSession *session;
	SoupMessage *msg;

	session = soup_session_new();
	msg = soup_message_new("GET", url);
	soup_message_headers_replace(msg->request_headers, "user-agent", "Chrome");
	soup_session_send_message(session, msg);
	responce = g_strdup(msg->response_body->data);
	g_object_unref(msg);
	g_object_unref(session);
	return responce;
}

const char *hhapi_parse_json(const char *json)
{
	const char *name, *currency;
	const char *result;
	JsonParser *parser;
	JsonObject *root_obj, *salary_obj;
	gint64 salary_from, salary_to;

	parser = json_parser_new();
	json_parser_load_from_data(parser, json, -1, NULL);
	root_obj = json_node_get_object(json_parser_get_root(parser));
	name = json_object_get_string_member(root_obj, "name");
	salary_obj = json_node_get_object(json_object_get_member(root_obj, "salary"));
	salary_from = json_object_get_int_member(salary_obj, "from");
	salary_to = json_object_get_int_member(salary_obj, "to");
	currency = json_object_get_string_member(salary_obj, "currency");

	result = g_strdup_printf("%s\nЗарплата от %ld до %ld %s\n",
		name, salary_from, salary_to, currency);  

	g_object_unref (parser);

	return result;
}

const char *hhapi_parse_json_items(const char *json)
{
	JsonParser	*parser;
	JsonObject	*root_object;
	JsonArray	*items_array;
	const char	*output;

	parser = json_parser_new();
	if (json_parser_load_from_data(parser, json, -1, NULL))
	{
		root_object = json_node_get_object(json_parser_get_root(parser));
		if (json_object_has_member(root_object, "items"))
		{
			items_array = json_object_get_array_member(root_object, "items");
			output = hhapi_parse_items_array(items_array);
		}
		else
			output = g_strdup("Cannot find items array");
	}
	else
		output = g_strdup("Cannot parse json");
	g_object_unref(parser);
	return output;
}

static const char *hhapi_parse_items_array(JsonArray *items_array)
{
	char		**vacancies;
	JsonObject	*vacancy_object;
	JsonNode	*vacancy_node;
	const char	*output;
	guint		items_len;

	items_len = json_array_get_length(items_array);
	vacancies = (char**) g_malloc0_n(items_len + 1, sizeof(char*));
	for (guint i = 0; i < items_len; i++)
	{
		vacancy_node = json_array_get_element(items_array, i);
		vacancy_object = json_node_get_object(vacancy_node);
		vacancies[i] = hhapi_parse_vacancy(vacancy_object);
	}
	output = g_strjoinv("=================================\n", vacancies);
	g_strfreev(vacancies);

	return output;
}

static char *hhapi_parse_vacancy(JsonObject *vacancy_object)
{
	JsonObject	*salary_object;
	JsonNode	*salary_node;
	char		*output;
	const char	*id;
	const char	*name;
	const char	*currency;
	guint64		salary_from;
	guint64		salary_to;

	id = hhapi_parse_string_member(vacancy_object, "id");
	name = hhapi_parse_string_member(vacancy_object, "name");
	if (!json_object_has_member(vacancy_object, "salary"))
	{
		output = g_strdup_printf("%s\n%s\nЗарплата: данные отсутствуют\n",
			id, name);
	}
	else
	{
		salary_node = json_object_get_member(vacancy_object, "salary");
		if (json_node_is_null(salary_node))
		{
			output = g_strdup_printf("%s\n%s\nЗарплата: данные отсутствуют\n",
				id, name);
		}
		else
		{
			salary_object = json_node_get_object(salary_node);
			salary_from = hhapi_parse_int_member(salary_object, "from");
			salary_to = hhapi_parse_int_member(salary_object, "to");
			if (salary_from == 0 && salary_to == 0)
				output = g_strdup_printf("%s\n%s\nЗарплата: данные отсутствуют\n",
					id, name);
			else
			{
				currency = hhapi_parse_string_member(salary_object, "currency");
				if (salary_from == 0 && salary_to != 0)
					output = g_strdup_printf("%s\n%s\nЗарплата до %lu %s\n",
						id, name, salary_to, currency);
				else if (salary_from != 0 && salary_to == 0)
					output = g_strdup_printf("%s\n%s\nЗарплата от %lu %s\n",
						id, name, salary_from, currency);
				else
					output = g_strdup_printf("%s\n%s\nЗарплата от %lu до %lu %s\n",
						id, name, salary_from, salary_to, currency);
			}
		}
	}
	return output;
}

static guint64 hhapi_parse_int_member(JsonObject *object, const char *member)
{
	if (!json_object_has_member(object, member))
		return 0;

	if (json_node_is_null(json_object_get_member(object, member)))
		return 0;

	return json_object_get_int_member(object, member);
}

static const char *hhapi_parse_string_member(JsonObject *object, const char *member)
{
	if (!json_object_has_member(object, member))
		return "";

	if (json_node_is_null(json_object_get_member(object, member)))
		return "";

	return json_object_get_string_member(object, member);
}
