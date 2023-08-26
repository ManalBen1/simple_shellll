#ifndef _SHELL_H_
#define _SHELL_H_

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <limits.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>


#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3
#define USE_STRTOK 0
#define USE_GETLINE 0
#define BUF_FLUSH -1
#define WRITE_BUF_SIZE 1024
#define READ_BUF_SIZE 1024
#define HIST_MAX	4096
#define HIST_FILE	".simple_shell_history"
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2
extern char **environ;

/**
 * struct liststr - Represents a singly linked list node.
 * @num: Number field
 * @str: String
 * @next: Pointer to next node
 */

typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct pass_infor - contains pseudo-arguements to pass into a function,
 *allowing uniform prototype for function pointer struct
 *@arg: string generated from getline with args
 *@argv: array of strings from arg
 *@history: the history node
 *@path: string path for current Command
 *@env: linked list local copy of environ
 *@environ: modified copy of environ from env
 *@alias: the alias node
 *@err_num: error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@argc: the argument count
 *@line_count: the error count
 *@env_changed: on if environ was changed
 *@readfile_descr: file descriptor from which to read line input
 *@histcount: history line number count
 *@status: return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 */

typedef struct pass_infor
{
	char *path;
	char **argv;
	char *arg;
	char *fname;
	char **environ;
	int argc;
	int err_num;
	int linecount_flag;
	int env_changed;
	int status;
	unsigned int line_count;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **cmd_buf;
/**
* pointer to cmd, chain buffer, for memory mangement
* CMD_type ||, &&, ;
*/

int cmd_buf_type;
int readfile_descr;
int histcount;
}
infor;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
0, 0, 0}

/**
 *struct builtin - contains builtin string & function
 *@type: builtin command flag
 *@func: function
 */
typedef struct builtin
{
	char *type;
	int (*func)(infor *);
} builtin_table;



int hsh(infor *, char **);
int find_builtin(infor *);
void find_cmd(infor *);
void fork_cmd(infor *);

int is_cmd(infor *, char *);
char *dup_chars(char *, int, int);
char *find_path(infor *, char *, char *);


int loophsh(char **);


void print_input_string(char *);
int write_char(char);
int _putfile_descr(char c, int file_descr);
int _putsfile_descr(char *str, int file_descr);


int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);


char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);


char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

char **strtow(char *, char *);
char **strtow2(char *, char);


char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

int _erratoi(char *);
void print_error(infor *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);


int bfree(void **);
int interactive(infor *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);


int _myexit(infor *);
int _mycd(infor *);
int _myhelp(infor *);


int _myhistory(infor *);
int _myalias(infor *);


ssize_t get_input(infor *);
int _getline(infor *, char **, size_t *);
void sigintHandler(int);


void clear_info(infor *);
void set_info(infor *, char **);
void free_info(infor *, int);


char *_getenv(infor *, const char *);
int _myenv(infor *);
int _mysetenv(infor *);
int _myunsetenv(infor *);
int populate_env_list(infor *);


char **get_environ(infor *);
int _unsetenv(infor *, char *);
int _setenv(infor *, char *, char *);


char *get_history_file(infor *info);
int write_history(infor *info);
int read_history(infor *info);
int build_history_list(infor *info, char *buf, int linecount);
int renumber_history(infor *info);

size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);


list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);
int is_chain(infor *, char *, size_t *);
void check_chain(infor *, char *, size_t *, size_t, size_t);
int replace_alias(infor *);
int replace_vars(infor *);
int replace_string(char **, char *);

#endif

