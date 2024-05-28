/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/26 14:27:59 by ferre         #+#    #+#                 */
/*   Updated: 2024/05/28 04:28:50 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_non_canonical(void)
{
	struct termios term;
	tcgetattr(1, &term);
	term.c_lflag &= ~ICANON;
	tcsetattr(1, TCSANOW, &term);
	return (0);
}

int	handle_promt(char *promt)
{
	char	*term_line;
	char 	**argv;
	//int		pid;

	term_line = readline(promt);
	if (!term_line)
		return (0);
	if (ft_strlen(term_line) != 0)
	{
		add_history(term_line);
		//pid = fork();
		//if (pid == 0)
		//{
		//	argv = ft_split(term_line, ' ');
		//	handle_command(argv, args_count(argv, 0));
		//	clean_args(argv);
		//	exit(EXIT_SUCCESS);
		//}
		//waitpid(pid, NULL, 0);
		argv = ft_split(term_line, ' ');
		handle_command(argv, args_count(argv, 0));
		printf("handled command\n");
		clean_args(argv);
	}
	free(term_line);
	return (1);
}

int	main(void)
{
	char		*promt;
	char		*cdir;

	set_non_canonical();
	signal(SIGINT, interrupt_shell);
	while (1)
	{
		cdir = getcwd(NULL, 0);
		promt = str_join_free(str_join_free(ft_strdup("-minishell-"), cdir), ft_strdup("$ "));
		if (!handle_promt(promt))
			break ;
		printf("handled promt\n");
		free(promt);
	}
	if (promt)
		free(promt);
	clear_history();
	printf("exiting shell\n");
	exit(EXIT_SUCCESS);
}
