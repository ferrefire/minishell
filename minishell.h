/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferrefire <ferrefire@student.42.fr>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/26 14:28:11 by ferre         #+#    #+#                 */
/*   Updated: 2024/05/31 14:48:35 by ferrefire     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <dirent.h>
#include <termios.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#define RE_OUT ">"
#define RE_OUT_APP ">>"
#define RE_IN "<"
#define RE_IN_DEL "<<"
#define PIPE "|"
#define METACHARS "> >> < << |"
#define BUILT_IN_CMD "cd pwd echo exit export unset env $?"
#define PARENT 1
#define CHILD 2

typedef struct data
{
    char **envp;
    char *command_line;
    char **commands;
    char *cdir;
}               t_data;

void interrupt_shell(int signal);
int exec_file(t_data *data);
int handle_command(t_data *data);
char *str_join_free(char *s1, char *s2, int f1, int f2);
char **clean_args(char **arr);
int args_count(char **args, int meta_break);
char **copy_args(char **args, int amount, int meta_break);
int direct(char **command);
int in_str(char *s, char *str);
int print_dir(char *path);
char *search_dir(char *file_name, char *dir_path);
char *find_file(char *file_name);
int get_exec(t_data *data);
int clean_shell(t_data *data);
int quit_shell(int exit_code, char *error, t_data *data);
int iterate_commands(t_data *data);
int clip_commands(t_data *data);

#endif