#include <stdio.h>

#include <json-c/json.h>

#include "json-parser.h"

static void json_print_type_string(json_object *jobj)
{
    enum json_type type;
    type = json_object_get_type(jobj);
    switch (type) {
    case json_type_string:
        printf("json_type_string val: %s\n", json_object_get_string(jobj));
        fflush(stdout);
        break;
    default:
        break;
    }
}

/* Look only into string types */
void json_print_parsed(char *json)
{
    json_object *jobj = NULL;
    enum json_type type = 0;

    jobj = json_tokener_parse(json);
    if (jobj == NULL) {
        fprintf(stderr, "%s error: invalid JSON string", __func__);
        return;
    }

    json_object_object_foreach(jobj, key, val)
    {
        type = json_object_get_type(val);
        switch (type) {
        case json_type_string:
            json_print_type_string(val);
            break;
        default:
            break;
        }
    }
}
