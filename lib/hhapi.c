#include <libsoup/soup.h>
#include <json-glib/json-glib.h>
#include "hhapi.h"

char *hhapi_get_request(const char *url)
{
	char *responce;
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

char *hhapi_parse_json(const char *json)
{
	const char *name, *currency;
	char *result;
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
