/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:48:06 by rgallego          #+#    #+#             */
/*   Updated: 2023/08/17 16:46:54 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "global.h"
#include "parser.h"
#include "lexer.h"
#include "executor.h"

t_global	g_sigenv;

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
	if (isstrspace(line))
		free(line);
	else if (line[ft_strlen(line) - 1] == '|'
		|| (ft_strrchr(line, '|') && isstrspace(ft_strrchr(line, '|') + 1)))
		mini_error(UNEXPECTED_TK_MSG, "|", SYNTAX_ERR, line);
	else
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
