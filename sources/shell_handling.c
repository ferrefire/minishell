/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_handling.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/18 18:27:32 by ferre         #+#    #+#                 */
/*   Updated: 2024/12/20 16:09:25 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <signal.h>
#include <termios.h>
#include <unistd.h>
#include <ctype.h>

int	g_var;

//Handles the shell prompt.
int	handle_prompt(t_data *data)
{
	data->prompt = readline(data->prompt_line);
	if (data->prompt == NULL)
		return (0);
	if (parse_commands(data))
	{
		running_child(1);
		process_commands(data);
		running_child(0);
	}
	else
	{
		data->error = ((2) << 8) & 0xff00;
		ft_putstr_fd("error: unexpected meta character\n", STDERR_FILENO);
	}
	clear(&data->ignore_commands);
	data->ignore_commands = ft_strdup("");
	if (ft_strlen(data->prompt) > 0 && data->prompt[0] != ' '
		&& !str_equals(data->prompt, data->previous_prompt))
	{
		add_history(data->prompt);
		clear(&data->previous_prompt);
		data->previous_prompt = ft_strdup(data->prompt);
	}
	clear(&data->prompt);
	return (1);
}

void	interrupt_shell(int signal)
{
	if (signal == SIGQUIT)
		printf("Quit (core dumped)");
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	if (g_var == 0)
		rl_redisplay();
}

void	set_signals(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~0001000;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	signal(SIGINT, interrupt_shell);
	signal(SIGQUIT, SIG_IGN);
}

void	running_child(int mode)
{
	g_var = mode;
	if (mode)
		signal(SIGQUIT, interrupt_shell);
	else
		signal(SIGQUIT, SIG_IGN);
}

int	find_env_char(char *str)
{
	int	i;
	int	size;

	i = find_chr(str, '$', 0, 0);
	size = ft_strlen(str);
	while (i != -1 && i + 1 < size)
	{
		if (str[i + 1] == '?')
			return (i);
		if (ft_isalnum(str[i + 1]) || str[i + 1] == '_')
			return (i);
		i = find_chr(str, '$', i + 1, 0);
	}
	return (-1);
}
