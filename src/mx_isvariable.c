#include "../inc/ush.h"

bool mx_isvariable (t_variable **list, char **k_v) {
    t_variable *pl = *list;

    while (pl) {
        if (mx_strcmp(k_v[0], pl->key) == 0) {
            if (k_v[1] != NULL) {
                mx_strdel(&pl->value);
                pl->value = mx_strdup(k_v[1]);
            }
            else
                mx_strdel(&pl->value);
            return false;
        }
        pl = pl->next;;
    }
    return true;
}
