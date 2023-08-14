/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:48:06 by rgallego          #+#    #+#             */
/*   Updated: 2023/08/14 12:36:36 by rgallego         ###   ########.fr       */
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
	if (!line)
		write (2, "\b\bexit\n", 7);
	add_history(line);
	errno = safe_errno;
	return (line);
}

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	t_token_list	*list;
	t_cmd			*cmd_list;

	(void)argc, (void)argv;
	signal(SIGINT, sig_normal);
	signal(SIGQUIT, SIG_IGN);
	line = get_line(errno);
	create_my_env(envp);
	while (line)
	{
		list = tokenize(&line);
		if (list)
		{
			cmd_list = lexer(&list);
			if (cmd_list)
				exec_main(&cmd_list);
		}
		signal(SIGINT, sig_normal);
		signal(SIGQUIT, SIG_IGN);
		line = get_line(errno);
	}
	delete_env_vbles();
	return (0);
}
