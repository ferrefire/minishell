/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/26 14:27:59 by ferre         #+#    #+#                 */
/*   Updated: 2024/05/28 07:23:27 by ferre         ########   odam.nl         */
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

int	handle_promt(char *prompt)
{
	char	*term_line;
	char 	**argv;

	term_line = readline(prompt);
	if (!term_line)
		return (0);
	if (ft_strlen(term_line) != 0)
	{
		printf("\n");
		add_history(term_line);
		argv = ft_split(term_line, ' ');
		handle_command(argv, args_count(argv, 0));
		clean_args(argv);
		printf("\n");
	}
	free(term_line);
	return (1);
}

int	main(void)
{
	char		*prompt;
	char		*cdir;

	signal(SIGINT, interrupt_shell);
	while (1)
	{
		cdir = getcwd(NULL, 0);
		prompt = str_join_free(str_join_free(ft_strdup("-minishell-"), cdir), ft_strdup("$ "));
		if (!handle_promt(prompt))
			break ;
		free(prompt);
	}
	if (prompt)
		free(prompt);
	clear_history();
	exit(EXIT_SUCCESS);
}
