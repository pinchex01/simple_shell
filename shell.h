#ifndef SHELL_H
#define SHELL_H

#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdarg.h>
#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>


#define BUFFER_SIZE_READ 1024
#define BUFFER_SIZE_WRITE 1024
#define MAX_WORD_COUNT 100
#define NEG_ONE -1
#define REG_FLAG 0
#define OR_FLAG 1
#define AND_FLAG 2
#define CHAIN_FLAG 3
#define BAS_CHANGE_LOWER 1
#define BAS_CHANGE_UNSIG 2
#define USE_GETLINE 0
#define USE_STRTOK 0
#define HIST_FILE_NAME ".ss_history"
#define HIST_SIZE_MAX 4096
#define SET_INFO							\
	{										\
		NULL, NULL, NULL, 0, 0, 0, 0,		\
		NULL, NULL, NULL, NULL, NULL,		\
		0, 0, NULL, 0, 0, 0					\
	}

extern char **environ;

/**
 * struct ListNode - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct ListNode
{
	int num;
	char *str;
	struct ListNode *next;
} list_s;

/**
 * struct internalNode - contains simulated arguments for a function pointer,
 *					 allowing for a consistent function prototype
 * @arg: a string generated from getline that holds arguments
 * @argv: an array of strings generated from @arg
 * @path: the path string for the current command
 * @argc: the number of arguments
 * @lines: the number of errors encountered
 * @error_code: the exit() error code
 * @lc_flag: a flag indicating whether this line of input should be counted
 * @prog_name: the name of the program's file
 * @env: a linked list representing a local copy of the environment variables
 * @environ: a custom-modified copy of the environ from the linked list env
 * @history: the node for the command history
 * @alias: the node for the command alias
 * @env_changed: a flag that indicates whether environ has been changed
 * @status: the return status of the most recent executed command
 * @sep_buff: the address of the pointer to sep_buff, used for chaining
 * @sep_buff_kind: the type of command buffer (CMD_type ||, &&, ;)
 * @fd_read: the file descriptor used for reading line input
 * @hist_lines: the number of lines in the history
 */

typedef struct internalNode
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	size_t lines;
	int error_code;
	int lc_flag;
	char *prog_name;
	list_s *env;
	list_s *history;
	list_s *alias;
	char **environ;
	int env_changed;
	int status;

	char **sep_buff;
	int sep_buff_kind;
	int st_read;
	int hist_lines;
} info_y;

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */

typedef struct builtin
{
	char *type;
	int (*func)(info_y *);
} builtin_commands;

int shell_control(info_y *info, char **av);
int write_char(char c, int fd);
int write_chars(char *str, int fd);
int _strlength_func(char *s);
int _strcmp_func(char *s1, char *s2);
int _putchar_err(char);
int _putchar(char);
int _isalpha(int);
int _atoi(char *);
int conv_error_num(char *);
int sshell_exit(info_y *);
int sshell_cd(info_y *);
int sshell_help(info_y *);
int sshell_history(info_y *);
int sshell_alias(info_y *);
int _getline(info_y *, char **, size_t *);
int _printenv(info_y *);
int check_setenvfunc(info_y *);
int check_unsetenvfunc(info_y *);
int _unsetenvfunc(info_y *, char *);
int _setenvfunc(info_y *, char *, char *);
void _errput(char *);
void _puts(char *);
char *_strcat_func(char *, char *);
char *_strcpy(char *, char *);
char *_strdup(const char *);
char *_strncpy_func(char *, char *, int);
char *_strncat_func(char *, char *, int);
char *_strchr_func(char *, char);
char *_memorysett(char *, char, unsigned int);
void *_realloc_func(void *ptr, unsigned int old_size, unsigned int new_size);
char *_getenvfunc(info_y *, const char *);
char *starts_with_func(const char *, const char *);
char *duplicate_char(char *, int, int);
char *file_path_check(info_y *info, char *pathstr, char *cmd);
char *change_base_num(long int, int, int);
char *read_hist_func(info_y *info);
char **get_env_func(info_y *);
char **strtowdelim(char *, char *);
char **list_to_vector_function(list_s *);
void check_command(info_y *);
void create_process(info_y *);
void handle_sigint(int);
void clear_info_func(info_y *);
void set_info_func(info_y *, char **);
void free_info_func(info_y *, int);
void free_vect_func(char **);
void print_error(info_y *, char *);
void rep_com(char *);
void free_list_func(list_s **);
void chain_checking_func(info_y *info, char *buf, size_t *p, size_t i, size_t len);
int handle_builtin(info_y *);
bool func_exe(info_y *, char *);
int loophsh(char **);
int bfree(void **);
int from_terminal_func(info_y *);
int print_dec_num(int, int);
int gather_envfunc(info_y *);
int create_history_func(info_y *info);
int read_history_func(info_y *info);
int update_history(info_y *info, char *buf, int linecount);
int increment_history(info_y *info);
int delete_node_at_index_func(list_s **, unsigned int);
bool is_chain_delimeter(info_y *, char *, size_t *);
int change_alias(info_y *);
int change_var_func(info_y *);
int change_string_func(char **, char *);
list_s *app_node(list_s **head, const char *str, int num);
list_s *preppend_node(list_s **head, const char *str, int num);
list_s *node_str_start_func(list_s *, char *, char);
size_t print_list_str_func(const list_s *);
size_t _listlen_func(const list_s *);
size_t print_list_func(const list_s *);
ssize_t get_input(info_y *);
ssize_t get_node_index_func(list_s *, list_s *);
char **split_stringfunc(char *str, char *separators, size_t *word_count);
int words_count(char *str, char *separators, unsigned int *arr);
void set_zeros_func(unsigned int *arr, size_t size);
void set_nulls_func(char *arr, size_t size);
bool is_delimiter(char c, char *delimiters);

#endif 

