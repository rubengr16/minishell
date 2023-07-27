/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:48:06 by rgallego          #+#    #+#             */
/*   Updated: 2023/07/27 20:54:16 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"
#include "global.h"
#include "parser.h"
#include "lexer.h"
#include "executor.h"

t_global g_sigenv;

void	discover_leaks(void)
{
	system("leaks minishell");
}

static char	*get_line(void)
{
	char	*result_line;
	char	*line;
	char	*aux;

	line = readline("minishell> ");
	if (line && *line && line[ft_strlen(line) - 1] == '|')
	{
		aux = NULL;
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
	add_history(line);
	return (line);
}

void	signalHandling(int sig)
{
	if (sig == SIGINT)
		write(1, "\n", 1);
	else if (sig == SIGQUIT)
		write(1, "exit\n", 5);
	else if (sig == SIGTERM)
		write(1, "Hola\n", 5);
}

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	t_token_list	*list;
	t_cmd			*cmd_list;

	(void)argc, (void)argv;
	signal(SIGINT, signalHandling);
	signal(SIGQUIT, signalHandling);
	line = get_line();
	create_my_env(envp);
	g_sigenv.last_status = ft_strdup("0");
	while (line)
	{
		list = tokenize(&line);
		if (list)
		{
			cmd_list = lexer(&list);
			if (cmd_list && !exec_main(&cmd_list))
				line = get_line();
			else
				line = NULL;
		}
		else
			line = NULL;
	}
	delete_env_vbles();
	return (0);
}
