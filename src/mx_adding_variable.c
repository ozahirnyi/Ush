#include "../inc/ush.h"

static void variable_error_printing(t_ush *ush, char *comn, int *count) {
    mx_printerr("ush: command not found: ");
    mx_printerr(comn);
    mx_printerr("\n");
    mx_variable_cleaning(ush, count);
}

static void exyta_condition(t_ush *ush, char **command,
                                                    char **k_v2, int *count) {
    if (mx_check_key_allow(NULL, k_v2[0])) {
        if (mx_isvariable (ush, k_v2)) {
            mx_push_back_variable(&ush->variable_list, k_v2);
            (*count)++;
        }
    }
    else {
        variable_error_printing(ush, command[ush->storage], count);
        ush->trigger = true;
    }
}

static void variable_adding_condition(t_ush *ush, char **command,
                                                    char **k_v2, int *count) {
    if (k_v2 != NULL )
        exyta_condition(ush, command, k_v2, count);
    else {
        mx_del_strarr(&k_v2);
        for (ush->storage += 1; command[ush->storage]; ush->storage++) {
            k_v2 = mx_key_value_creation(ush, command[ush->storage]);
            if (k_v2 == NULL)
                mx_variable_cleaning(ush, count);
            mx_del_strarr(&k_v2);
        }
        ush->trigger = true;;
    }
}

static void variable_adding_cycle(t_ush *ush, char **command,
                                                    char **k_v2, int *count) {
    for (int i = 1; command[i]; i++) {
        k_v2 = mx_key_value_creation(ush, command[i]);
        if (k_v2 != NULL || ush->equals) {
            ush->storage = i;
            variable_adding_condition(ush, command, k_v2, count);
            if (ush->trigger == true) {
                ush->trigger = false;
                ush->equals = false;
                mx_del_strarr(&k_v2);
                break;
            }
            ush->equals = false;
        }
        else {
            variable_error_printing(ush, command[i], count);
        }
        mx_del_strarr(&k_v2);
    }
}
void mx_adding_variable(t_ush *ush, char **command, char **kv) {
    char **k_v2 = NULL;
    int count = 1;

    if (mx_isvariable(ush, kv)) {
        mx_push_back_variable(&ush->variable_list, kv);
        count++;
    }
    variable_adding_cycle(ush, command, k_v2, &count);
    ush->storage = 0;
}
