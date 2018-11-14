#include <libsoup/soup.h>
#include "hhapi.h"

char *hhapi_get_request(const char *url)
{
	gchar *responce;
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
	return g_strdup(json);
}
