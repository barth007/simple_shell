#ifndef  HEADER_H
#define HEADER_H


#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>


/* for read/write buffers */
#define READ_BUFF_SIZE 1024
#define WRITE_BUFF_SIZE 1024
#define TRUE 1

/*----start of source of input-----*/
#define EOF             (-1)
#define ERRCHAR         ( 0)
#define INIT_SRC_POS    (-2)
struct source_s
{   
    char *buffer;       /* the input text */
    long bufsize;       /* size of the input text */
    long  curpos;       /* absolute char position in source */
};
char next_char(struct source_s *src);
void unget_char(struct source_s *src);
char peek_char(struct source_s *src);
void skip_white_spaces(struct source_s *src);
/*--- end of source of input---*/

/*-----start of  scanner input---- */
struct token_s
{
    struct source_s *src;       /* source of input */
    int    text_len;            /* length of token text */
    char   *text;               /* token text */
};
/* the special EOF token, which indicates the end of input */
extern struct token_s eof_token;
struct token_s *tokenize(struct source_s *src);
void free_token(struct token_s *tok);
int  parse_and_execute(struct source_s *src);
/*---- end of scanner input---- */

/*--- start of parser---- */
struct node_s *parse_simple_command(struct token_s *tok);
/*--- end of parser---*/

/*----start of creating a node----*/
enum node_type_e
{
    NODE_COMMAND,           /* simple command */
    NODE_VAR,               /* variable name (or simply, a word) */
};
enum val_type_e
{
    VAL_SINT = 1,       /* signed int */
    VAL_UINT,           /* unsigned int */
    VAL_SLLONG,         /* signed long long */
    VAL_ULLONG,         /* unsigned long long */
    VAL_FLOAT,          /* floating point */
    VAL_LDOUBLE,        /* long double */
    VAL_CHR,            /* char */
    VAL_STR,            /* str (char pointer) */
};
union symval_u
{
    long               sint;
    unsigned long      uint;
    long long          sllong;
    unsigned long long ullong;
    double             sfloat;
    long double        ldouble;
    char               chr;
    char              *str;
};
struct node_s
{
    enum   node_type_e type;    /* type of this node */
    enum   val_type_e val_type; /* type of this node's val field */
    union  symval_u val;        /* value of this node */
    int    children;            /* number of child nodes */
    struct node_s *first_child; /* first child node */
    struct node_s *next_sibling, *prev_sibling;
                                /*
                                 * if this is a child node, keep
                                 * pointers to prev/next siblings
                                 */
};
struct  node_s *new_node(enum node_type_e type);
void    add_child_node(struct node_s *parent, struct node_s *child);
void    free_node_tree(struct node_s *node);
void    set_node_val_str(struct node_s *node, char *val);
/*-----end of creating a node -----*/
/*-------start of executor part--------*/
char *search_path(char *file);
int do_exec_cmd(int argc, char **argv);
int do_simple_command(struct node_s *node);
/*----------end of executor part--------*/
/*tokenization*/
char *read_input(void);
/*print the prompt*/
void main_prompt(void);
void main_prompt2(void);

/*execute binary files*/
void exe_command(char **);

/*get location or full path of command */
char *get_path(char *);

/*-----------------start of self built function------------*/
char *_memcpy(char *dest, char *src, size_t n);
int _putchar(char);
#endif
