#ifndef USH_H
#define USH_H

/* DEFINES */

#define MX_EBUF "ush: Buffer cannot be longer than terminal width.\n"
#define MX_ETGTN "ush: Could not access the termcap data base.\n"
#define MX_EBFLOC "ush: Buffer cannot allocate enough memory.\n"
#define MX_PIZDA "ush: Pizda! Character error -- '%c'\n"

/* -------- */

/* INClUDES */

// FRONT-END
#include <fcntl.h>
#include <termios.h>
#include <term.h>

#include <stdio.h>
#include <string.h>

#include "libmx/inc/libmx.h"

/* -------- */

/* DECLARATIONS */

typedef struct termios t_term;

typedef struct s_termconf {
    t_term tty;
    t_term savetty;
}              t_termconf;

typedef struct s_t_node {
    char *text;
    struct s_t_node *next;
}              t_t_node;

typedef struct s_b_node {
    t_t_node *t_node;
    struct s_b_node *next;
}              t_b_node;

typedef struct s_ush {
    int exit_code;
    bool active;
    int buf_size;
    char *buf;
    t_termconf *termconf;
    t_b_node *blocks;
}              t_ush;

t_ush *mx_create_ush();
void mx_dealloc_ush(t_ush **ush);

t_termconf *mx_create_termconf();
void mx_read_termconf(t_termconf *termconf);
void mx_dealloc_termconf(t_termconf **termconf);

short mx_get_buf_type(char ch);

int mx_buf_drop(char **buf, int *buf_size);
int mx_buf_push(char **buf, int *buf_size, char ch);

t_t_node *mx_create_text_node(char *text);
void mx_pop_t_node_front(t_t_node **head);
void mx_push_t_node_back(t_t_node **head, char *text);

int mx_lstlen(t_b_node **head);
t_b_node *mx_create_block_node(t_t_node *t_node);
void mx_pop_block_front(t_b_node **head);
t_b_node *mx_push_block_back(t_b_node **head, t_t_node *t_node);
void mx_dealloc_blocks(t_b_node **head);

// STRING OPERATIONS && PARSING
void mx_parse_buf(t_ush *ush);
t_b_node *mx_parse_block(t_t_node **head);
char *mx_space_parse(char *str, int *piv);
char *mx_text_parse(char *str, int *piv);
char *mx_sinmrk_parse(char *str, int *piv);
char *mx_doumrk_parse(char *str, int *piv);

void mx_restore_buffer(t_ush *ush);
int mx_term_width_check(t_ush *ush, int *len, int *term);

int mx_get_twidth();

int mx_read_input(t_ush *ush);

/* -------- */

#endif
