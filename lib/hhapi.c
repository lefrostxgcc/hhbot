#include <libsoup/soup.h>
#include <json-glib/json-glib.h>
#include "hhapi.h"

struct Salary
{
	char *from;
	char *to;
};

static struct VacancyArray parse_items_array(JsonArray *items_array);
static char *parse_int_member(JsonObject *object, const char *member);
static char *parse_string_member(JsonObject *object, const char *member);
static struct Vacancy create_vacancy(JsonObject *vacancy_object);
static struct Salary parse_salary(JsonObject *vacancy_object);
static char *parse_address(JsonObject *vacancy_object);
static char *parse_employer_name(JsonObject *vacancy_object);
static void free_vacancy(struct Vacancy *vacancy);
static char *parse_address_object(JsonObject *adress_object);

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

struct VacancyArray hhapi_parse_json_items(const char *json)
{
	JsonParser			*parser;
	JsonObject			*root_object;
	JsonArray			*items_array;
	struct VacancyArray	vacancies;

	vacancies.data = NULL;
	vacancies.size = 0;
	parser = json_parser_new();
	if (json_parser_load_from_data(parser, json, -1, NULL))
	{
		root_object = json_node_get_object(json_parser_get_root(parser));
		if (json_object_has_member(root_object, "items"))
		{
			items_array = json_node_get_array(json_object_get_member(
				root_object, "items"));
			vacancies = parse_items_array(items_array);
		}
	}
	g_object_unref(parser);
	return vacancies;
}

void hhapi_free_vacancies(struct VacancyArray *vacancies)
{
	for (int i = 0; i < vacancies->size; i++)
		free_vacancy(&vacancies->data[i]);

	vacancies->data = NULL;
	vacancies->size = 0;
}

static void free_vacancy(struct Vacancy *vacancy)
{
	g_free(vacancy->id);
	g_free(vacancy->name);
	g_free(vacancy->salary_from);
	g_free(vacancy->salary_to);
	g_free(vacancy->employer_name);
	g_free(vacancy->address);
	g_free(vacancy->info);
}

struct VacancyArray parse_items_array(JsonArray *items_array)
{
	struct VacancyArray	vacancies;
	JsonObject			*vacancy_object;
	JsonNode			*vacancy_node;

	vacancies.size = json_array_get_length(items_array);
	vacancies.data = (struct Vacancy*) g_malloc0_n(vacancies.size,
		sizeof(struct Vacancy));
	for (int i = 0; i < vacancies.size; i++)
	{
		vacancy_node = json_array_get_element(items_array, i);
		vacancy_object = json_node_get_object(vacancy_node);
		vacancies.data[i] = create_vacancy(vacancy_object);
	}
	return vacancies;
}

static struct Vacancy create_vacancy(JsonObject *vacancy_object)
{
	struct Vacancy	vacancy;
	struct Salary	salary;

	vacancy.id = parse_string_member(vacancy_object, "id");
	vacancy.name = parse_string_member(vacancy_object, "name");
	salary = parse_salary(vacancy_object);
	vacancy.salary_from = salary.from;
	vacancy.salary_to = salary.to;
	vacancy.employer_name = parse_employer_name(vacancy_object);
	vacancy.address = parse_address(vacancy_object);
	vacancy.info = parse_string_member(vacancy_object, "description");
	return vacancy;
}

static struct Salary parse_salary(JsonObject *vacancy_object)
{
	struct Salary 	salary;
	JsonNode		*salary_node;
	JsonObject		*salary_object;

	if (!json_object_has_member(vacancy_object, "salary"))
	{
		salary.from = g_strdup("-");
		salary.to = g_strdup("-");
	}
	else
	{
		salary_node = json_object_get_member(vacancy_object, "salary");
		if (json_node_is_null(salary_node))
		{
			salary.from = g_strdup("-");
			salary.to = g_strdup("-");
		}
		else
		{
			salary_object = json_node_get_object(salary_node);
			salary.from = parse_int_member(salary_object, "from");
			salary.to = parse_int_member(salary_object, "to");
		}
	}
	return salary;
}

static char *parse_employer_name(JsonObject *vacancy_object)
{
	char		*name;
	JsonNode	*employer_node;
	JsonObject	*employer_object;

	if (!json_object_has_member(vacancy_object, "employer"))
	{
		name = g_strdup("-");
	}
	else
	{
		employer_node = json_object_get_member(vacancy_object, "employer");
		if (json_node_is_null(employer_node))
		{
			name = g_strdup("-");
		}
		else
		{
			employer_object = json_node_get_object(employer_node);
			name = parse_string_member(employer_object, "name");
		}
	}
	return name;
}

static char *parse_address(JsonObject *vacancy_object)
{
	char			*address;
	JsonNode		*address_node;
	JsonObject		*address_object;

	if (!json_object_has_member(vacancy_object, "address"))
	{
		address = g_strdup("-");
	}
	else
	{
		address_node = json_object_get_member(vacancy_object, "address");
		if (json_node_is_null(address_node))
		{
			address = g_strdup("-");
		}
		else
		{
			address_object = json_node_get_object(address_node);
			address = parse_address_object(address_object);
		}
	}
	return address;
}

static char *parse_address_object(JsonObject *address_object)
{
	char	*address;
	char	*city;
	char	*street;
	char	*building;

	city = parse_string_member(address_object, "city");
	street = parse_string_member(address_object, "street");
	building = parse_string_member(address_object, "building");
	if (!g_strcmp0(city, ""))
		address = g_strdup("-");
	else
		address = g_strjoin(", ", city, street, building, NULL);
	g_free(city);
	g_free(street);
	g_free(building);

	return address;
}

static char *parse_int_member(JsonObject *object, const char *member)
{
	if (!json_object_has_member(object, member))
		return g_strdup("");
	if (json_node_is_null(json_object_get_member(object, member)))
		return g_strdup("");
	return g_strdup_printf("%lu", json_object_get_int_member(object, member));
}

static char *parse_string_member(JsonObject *object, const char *member)
{
	if (!json_object_has_member(object, member))
		return g_strdup("");
	if (json_node_is_null(json_object_get_member(object, member)))
		return g_strdup("");
	return g_strdup(json_object_get_string_member(object, member));
}
