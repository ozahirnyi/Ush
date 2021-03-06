#include "../inc/ush.h"

static int slash_handling(char **res, char *str, int *i) {
    int sl_num = mx_count_slashes(&str[*i]);

    if (sl_num == 1) {
        if (!mx_one_slash_sinmrk(res, str, i))
            return mx_break_on_error(res) == NULL ? 0 : 0;
    }
    else if (sl_num == 2) {
        if (!mx_two_slash_sinmrk(res, str, i))
            return mx_break_on_error(res) == NULL ? 0 : 0;
    }
    else if (sl_num == 3) {
        if (!mx_three_slash_sinmrk(res, str, i))
            return mx_break_on_error(res) == NULL ? 0 : 0;
    }
    else if (sl_num == 4) {
        if (!mx_four_slash_sinmrk(res, str, i))
            return mx_break_on_error(res) == NULL ? 0 : 0;
    }
    return 1;
}

char *mx_sinmrk_parse(char *str, int *piv) {
    char *res = mx_strnew_x(1);
    int len = mx_strlen(str);
    int i = 0;

    while (i <= len) {
        if (str[i] == '\0')
            return mx_break_on_error(&res);
        else if (str[i] == '\\')
            slash_handling(&res, str, &i);
        else if (str[i] == '\'')
            break;
        else
            mx_push_symbol_l(&res, str[i]);
        i++;
    }
    (*piv) += i + 1;
    return res;
}
