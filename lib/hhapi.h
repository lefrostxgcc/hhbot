#ifndef HHAPI_H
#define HHAPI_H

const char *hhapi_get_request(const char *url);
const char *hhapi_parse_json(const char *json);
const char *hhapi_parse_json_items(const char *json);

#endif /* HHAPI_H */
