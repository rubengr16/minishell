/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: socana-b <socana-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:48:06 by rgallego          #+#    #+#             */
/*   Updated: 2023/08/17 16:25:14 by socana-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "global.h"
#include "parser.h"
#include "lexer.h"
#include "executor.h"

t_global	g_sigenv;

void	discover_leaks(void)
{
	system("leaks minishell");
}

static char	*get_line(int safe_errno)
{
	char	*line;

	line = readline("minishell$ ");
	if (g_sigenv.signal == SIGINT)
		errno = 1;
	if (line && *line)
		add_history(line);
	if (g_sigenv.signal != SIGINT)
		errno = safe_errno;
	return (line);
}

char	*aux_func(char *line, t_token_list *list, t_cmd *cmd_list)
{
	if (!isstrspace(line))
	{
		list = tokenize(&line);
		if (list)
		{
			cmd_list = lexer(&list);
			if (cmd_list)
				exec_main(&cmd_list);
		}
		g_sigenv.signal = 0;
		signal(SIGINT, sig_normal);
		signal(SIGQUIT, SIG_IGN);
	}
	else
		free(line);
	return (get_line(errno));
}

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	t_token_list	*list;
	t_cmd			*cmd_list;

	list = NULL;
	cmd_list = NULL;
	(void)argc, (void)argv;
	g_sigenv.signal = 0;
	signal(SIGINT, sig_normal);
	signal(SIGQUIT, SIG_IGN);
	line = get_line(errno);
	create_my_env(envp);
	while (line)
		line = aux_func(line, list, cmd_list);
	if (!line)
		ft_putendl_fd("exit", STDERR_FILENO);
	delete_env_vbles();
	return (0);
}
