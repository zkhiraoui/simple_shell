#ifndef SHELL_MACROS_H
#define SHELL_MACROS_H

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".history"
#define HIST_MAX	4096

extern char **environ;

typedef struct singly_linked_list {
	int num;
	char *str;
	struct singly_linked_list *next;
} list_t;

typedef struct ExecutionInfo {
	char *arg, **argv, *path, *file_name, **environ, **command_buf;
	list_t *env, *history, *alias;
	int argc, err_num, linecount_flag, environ_changed, cmd_status, buf_format, readfd, history_count;
	unsigned int line_count;
} info_t;

#define INFO_INIT { NULL }

#endif /* SHELL_MACROS_H */
