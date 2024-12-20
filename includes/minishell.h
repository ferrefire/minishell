/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/18 17:21:40 by ferre         #+#    #+#                 */
/*   Updated: 2024/12/20 18:24:33 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define META " \t><|"
# define RE "> < >> << |"
# define RE_OUT ">"
# define RE_IN "<"
# define RE_OUT_APP ">>"
# define RE_IN_LIM "<<"
# define PIPE "|"

extern int	g_var;
typedef struct data
{
	char	**environment;
	char	*prompt;
	char	*previous_prompt;
	char	**commands;
	char	*ignore_commands;
	int		error;
	int		forked;
	char	**open_fds;
	char	*prompt_line;
}				t_data;

typedef struct quote
{
	int	start;
	int	end;
	int	type;
	int	complete;
}				t_quote;

void	clean(int status, t_data *data);
void	clear(void *address);
int		error_message(int status, char *message, char *to_free);

char	*add_str(const char *s1, const char *s2);
int		str_equals(const char *s1, const char *s2);
int		str_append(char **address, char *str);
void	str_replace(char **address, char *replace, int start, int end);
char	*str_token(char **str, char token);

int		find_str(char *haystack, char *needle, int size);
int		find_chr(char *haystack, char needle, int offset, int not);
int		find_meta(char *haystack, int offset);
int		find_non_alnum(char *haystack, int offset);
int		find_env_char(char *str);
t_quote	find_quote(char *str, int start);

int		handle_prompt(t_data *data);
int		parse_commands(t_data *data);
int		run_command(t_data *data);
int		process_commands(t_data *data);
void	iterate_commands(t_data *data);
void	clip_commands(t_data *data);
int		valid_meta(int next, t_data *data);

int		direct(t_data *data);
int		redirect_stream(int fd, int redirect_fd, int forced, t_data *data);
int		pipe_output(t_data *data);
int		direct_repeat(int next, int forced, t_data *data);
int		read_until_del(char *delimiter, t_data *data);

int		print_env(t_data *data);
char	*get_env(char *key, int val, t_data *data);
void	set_env(char *key, t_data *data);
void	replace_env(char **addres, t_data *data);

int		echo(t_data *data);
int		cd(t_data *data);
int		execute(t_data *data);
int		export(t_data *data);
int		unset(t_data *data);
int		exit_shell(t_data *data);
int		run_built_in(t_data *data);

int		next_direct(int offset, t_data *data);
char	**copy_args(char **args, int size);
int		resize_args(void *address, int size);
int		clear_args(void *address);
int		args_size(char **args);
int		add_to_args(void *address, char *arg);
int		remove_from_args(void *address, char *arg);

void	interrupt_shell(int signal);
void	set_signals(void);
void	running_child(int mode);

char	*build_full_path(char *dir_path, char *file_name);
char	*search_dir(char *file_name, char *dir_path);
char	*find_file(char *file_name, t_data *data);
int		modify_directory(char *dir, t_data *data);

#endif