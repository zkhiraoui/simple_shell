#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include "shell_macros.h"

typedef struct built_in { char *type; int (*func)(info_t *); } built_in_table;

int run_command(info_t *, char **);
int find_built_in(info_t *);
int is_known_cmd(info_t *, char *);
int loop_cmd(char **);
int error_putchar(char);
int error_putfd(char c, int fd);
int error_putsfd(char *str, int fd);
int string_strlen(char *);
int string_strcmp(char *, char *);
int _putchar(char);
int free_block(void **);
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);
int _erratoi(char *);
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);
int _myhistory(info_t *);
int _myalias(info_t *);
int print_d(int, int);
int _getline(info_t *, char **, size_t *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);
int delete_node_at_index(list_t **, unsigned int);
int is_chain(info_t *, char *, size_t *);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);
int print_alias(list_t *node);
int set_alias(info_t *info, char *str);

char *copy_chars(char *, int, int);
char *find_path(info_t *, char *, char *);
char *string_prefix_equal(const char *, const char *);
char *string_strcat(char *, char *);
char *string_cpy(char *, char *);
char *string_dupy(const char *);
char *exit_strncpy(char *, char *, int);
char *exit_strncat(char *, char *, int);
char *exit_strchr(char *, char);
char **strtow(char *, char *);
char **strtow2(char *, char);
char *_memset(char *, char, unsigned int);
char *convert_number(long int, int, int);
char *_getenv(info_t *, const char *);
char **get_environ(info_t *);
char *get_history_file(info_t *info);
char **list_to_strings(list_t *);

list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
list_t *node_string_prefix_equal(list_t *, char *, char);

void find_cmd(info_t *);
void fork_cmd(info_t *);
void error_puts(char *);
void _puts(char *);
void deallocate(char **);
void *_realloc(void *, unsigned int, unsigned int);
void print_error(info_t *, char *);
void remove_comments(char *);
void sigintHandler(int);
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);
void free_list(list_t **);
void check_chain(info_t *, char *, size_t *, size_t, size_t);

size_t list_len(const list_t *);
size_t print_list(const list_t *);
size_t print_list_str(const list_t *);

ssize_t get_input(info_t *);
ssize_t get_node_index(list_t *, list_t *);
ssize_t input_buf(info_t *info, char **buf, size_t *len);
ssize_t read_buf(info_t *info, char *buf, size_t *len);

#endif
