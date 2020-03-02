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
#include "../libmx/inc/libmx.h"
//#include "libmx.h"

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

typedef struct s_env {
    char *key;
    char *value;
    struct s_env *next;
}              t_env;

typedef struct s_export {
    char *key;
    char *value;
    struct s_export *next;
}              t_export;

typedef struct s_variable {
    char *key;
    char *value;
    struct s_variable *next;
}              t_variable;

typedef struct s_ush {
    int exit_code;
    bool active;
    int buf_size;
    char *buf;
    t_termconf *termconf;
    t_b_node *blocks;
    t_export *export_list;
    t_variable *variable_list;
}              t_ush;

char *mx_space_parse(char *str, int *piv);
char *mx_text_parse(char *str, int *piv);
char *mx_sinmrk_parse(char *str, int *piv);
char *mx_doumrk_parse(char *str, int *piv);
int mx_buf_drop(char **buf, int *buf_size);
int mx_buf_push(char **buf, int *buf_size, char ch);
int mx_get_twidth();
int mx_lstlen(t_b_node **head);
int mx_read_input(t_ush *ush);
int mx_strarrlen(char **arr);
int mx_term_width_check(t_ush *ush, int *len, int *term);
short mx_get_buf_type(char ch);
// t_env *mx_envnode_creation(void);
t_export *mx_exportnode_creation(void);
t_b_node *mx_create_block_node(t_t_node *t_node);
t_b_node *mx_parse_block(t_t_node **head);
t_b_node *mx_push_block_back(t_b_node **head, t_t_node *t_node);
t_termconf *mx_create_termconf();
t_t_node *mx_create_text_node(char *text);
t_ush *mx_create_ush();
void mx_check_commands(t_ush *ush, char **line, char **env);
void mx_dealloc_blocks(t_b_node **head);
void mx_dealloc_termconf(t_termconf **termconf);
void mx_dealloc_ush(t_ush **ush);
void mx_export(t_export **export_list, char **command, char **env);
void mx_parse_buf(t_ush *ush);
void mx_pop_block_front(t_b_node **head);
void mx_pop_front_export(t_export **head);
void mx_pop_front_variable(t_variable **head);
void mx_pop_t_node_front(t_t_node **head);
void mx_process_creator(char **line);
void mx_push_t_node_back(t_t_node **head, char *text);
void mx_push_back_export(t_export **export, char **kv);
void mx_read_environment(t_export **export_list, char **env);
void mx_read_termconf(t_termconf *termconf);
void mx_restore_buffer(t_ush *ush);

// STRING OPERATIONS && PARSING

/* -------- */

#endif
