#include "../inc/ush.h"

static int c_cases(t_termconf **cfg, unsigned char ch, short type) {
    if (type == 0 && (*cfg)->ful_len < (*cfg)->term_w - 1) {
        (*cfg)->c_pos += 1;
        return mx_push_n_char(cfg, ch);
    }
    else if (type == 1) {
        (*cfg)->c_pos -= 1;
        return mx_drop_n_char(cfg);
    }
    else if (type == 2)
        (*cfg)->c_pos -= 1;
    else if (type == 3)
        (*cfg)->c_pos += 1;
    else if (type == 4 || type == 5)
        return mx_set_history_pos(cfg, type);
    else if (type == 101)
        return 101;
    else if (type == 102 && !(mx_strlen((*cfg)->chsn->buf)))
        return 102;
    return 0;
}

static void on_read_start(t_termconf **cfg) {
    tcsetattr(0, TCSAFLUSH, &((*cfg)->tty));
    mx_rd_print_color(cfg);
}

static int reading_cycle(t_termconf **cfg) {
    unsigned char ch[4] = {0, 0, 0, 0};
    char *buf = NULL;
    int exit_code = 0;

    while (1) {
        mx_restore_ch(ch);
        read(0, ch, 4);
        if (mx_term_width_check(cfg))
            return 1;
        if (ch[0] == '\n' && !ch[1] && !ch[2] && !ch[3])
            break;
        if ((exit_code = c_cases(cfg, ch[0], mx_get_buf_type(ch))))
            return exit_code;
        if (mx_term_width_check(cfg))
            return 1;
        buf = (*cfg)->chsn->buf;
        mx_rd_print_pbc(cfg, buf);
    }
    return 0;
}

static int on_read_ended(t_termconf **cfg) {
    t_h_node *clone = (*cfg)->chsn;
    char *new_buf = mx_strdup_x(clone->buf);
    int exit_code = 0;

    tcsetattr(0, TCSAFLUSH, &((*cfg)->savetty));
    mx_rd_print_old(cfg);
    exit_code = mx_history_handler(cfg, new_buf);
    return exit_code;
}

int mx_read_input_pro(t_ush *ush) {
    t_termconf **cfg = &(ush->termconf);
    int exit_code = 1;

    mx_init_clone(cfg);
    if (!isatty(0))
        return mx_read_from_thread(ush);
    if ((*cfg)->isInThread)
        mx_open_tty(cfg);
    on_read_start(cfg);
    if ((exit_code = reading_cycle(cfg)))
        return exit_code;
    if ((exit_code = on_read_ended(cfg)))
        return exit_code;
    return MX_RIP_BAD_EXIT;
}
