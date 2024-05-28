/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/26 14:28:11 by ferre         #+#    #+#                 */
/*   Updated: 2024/05/28 06:57:51 by ferre         ########   odam.nl         */
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

void interrupt_shell(int signal);
int exec_file(char **command);
int handle_command(char **command, int count);
char *str_join_free(char *s1, char *s2);
char **clean_args(char **arr);
int args_count(char **args, int meta_break);
char **copy_args(char **args, int amount, int meta_break);
int direct(char **command, char **piped_args);
int is_metachar(char *command);
int print_dir(char *path);
char *search_dir(char *file_name, char *dir_path);
char *find_file(char *file_name);

#endif