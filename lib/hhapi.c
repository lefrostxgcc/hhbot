#include <libsoup/soup.h>
#include "hhapi.h"

const char *hhapi_get_request(const char *url)
{
	SoupSession *session;
	SoupMessage *msg;
	GInputStream *stream;
	GError *error = NULL;

	session = soup_session_new();
	msg = soup_message_new("GET", url);
	soup_message_headers_replace(msg->request_headers, "user-agent", "Chrome");
	soup_session_send_message(session, msg);
	return msg->response_body->data;
}
