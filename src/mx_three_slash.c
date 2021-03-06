#include "../inc/ush.h"

int mx_three_slash(char **res, char *str, int *i) {
    (*i) += 3;
    if (str[(*i)] == '\0') {
        return mx_break_on_error(res) == NULL ? 0 : 0;
    }
    else {
        mx_push_symbol_l(res, '\\');
        return mx_push_symbol_l(res, str[(*i)]);
    }
}
