/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferrefire <ferrefire@student.42.fr>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/26 14:27:59 by ferre         #+#    #+#                 */
/*   Updated: 2024/05/31 15:00:20 by ferrefire     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_non_canonical(void)
{
	struct termios term;
	tcgetattr(0, &term);
	term.c_lflag &= ~ICANON;
	tcsetattr(0, TCSANOW, &term);
}

int	handle_promt(char *prompt, t_data *data)
{
	data->command_line = readline(prompt);
    if (!data->command_line)
        return (0);
    if (ft_strlen(data->command_line) != 0)
    {
        data->commands = ft_split(data->command_line, ' ');
        if (args_count(data->commands, 0) > 0)
        {
            add_history(data->command_line);
            handle_command(data);
            data->commands = clean_args(data->commands);
        }
	}
    free(data->command_line);
    return (1);
}

int	main(int argc, char **argv, char **envp)
{
    t_data      *data;
	char		*prompt;

    if (argc != 1)
    {
        printf("%s: no arguments allowed\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    data = malloc(sizeof(t_data));
    if (!data)
        exit(EXIT_FAILURE);
    data->envp = envp;
    signal(SIGINT, interrupt_shell);
	while (1)
	{
        if (data->cdir)
            free(data->cdir);
        data->cdir = getcwd(NULL, 0);
        prompt = str_join_free(ft_strjoin("-minishell-", data->cdir), "$ ", 1, 0);
		if (!handle_promt(prompt, data))
			break ;
		free(prompt);
	}
	if (prompt)
		free(prompt);
    clear_history();
    clean_shell(data);
    exit(EXIT_SUCCESS);
}
