/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:48:06 by rgallego          #+#    #+#             */
/*   Updated: 2023/08/15 13:43:27 by rgallego         ###   ########.fr       */
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
	char	*result_line;
	char	*line;
	char	*aux;

	line = readline("minishell> ");
	if (line && *line && line[ft_strlen(line) - 1] == '|')
	{
		while (line[ft_strlen(line) - 1] == '|')
		{
			aux = readline("> ");
			if (aux && *aux)
			{
				result_line = ft_strjoin(line, aux);
				free(line);
				line = result_line;
			}
			free(aux);
			aux = NULL;
		}
	}
	if (line && *line)
		add_history(line);
	errno = safe_errno;
	return (line);
}

char	*aux_func(char *line, t_token_list *list, t_cmd *cmd_list)
{
	if (!isstrspace(line))
	{
		g_sigenv.signal = 0;
		list = tokenize(&line);
		if (list)
		{
			cmd_list = lexer(&list);
			if (cmd_list)
				exec_main(&cmd_list);
		}
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
		write (2, "\b\bexit\n", 7);
	delete_env_vbles();
	return (0);
}
