#ifndef HHAPI_H
#define HHAPI_H

struct Vacancy
{
	char	*id;
	char	*name;
	char	*salary_from;
	char	*salary_to;
	char	*employer_name;
	char	*address;
	char	*info;
};

struct VacancyArray
{
	struct Vacancy	*data;
	int				size;
};

char				*hhapi_get_request(const char *url);
struct VacancyArray	hhapi_parse_json_items(const char *json);
void				hhapi_free_vacancies(struct VacancyArray *vacancies);

#endif /* HHAPI_H */
