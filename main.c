/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/26 14:27:59 by ferre         #+#    #+#                 */
/*   Updated: 2024/05/26 21:30:14 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_promt(char *promt)
{
	char	*term_line;
	char 	**argv;

	term_line = readline(promt);
	if (!term_line)
		return (0);
	if (ft_strlen(term_line) != 0)
	{
		add_history(term_line);
		argv = ft_split(term_line, ' ');
		handle_command(argv, args_count(argv));
		clean_args(argv);
	}
	free(term_line);
	return (1);
}

int	main(void)
{
	char		*promt;
	char		*cdir;

	signal(SIGINT, interrupt_shell);
	while (1)
	{
		cdir = getcwd(NULL, 0);
		promt = str_join_free(str_join_free(ft_strdup("-minishell-"), cdir), ft_strdup("$ "));
		if (!handle_promt(promt))
			break ;
		free(promt);
	}
	if (promt)
		free(promt);
	clear_history();
	exit(EXIT_SUCCESS);
}
