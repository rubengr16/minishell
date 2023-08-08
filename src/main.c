/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: socana-b <socana-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:48:06 by rgallego          #+#    #+#             */
/*   Updated: 2023/08/01 19:48:12 by socana-b         ###   ########.fr       */
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
	if (!line)
		write (2, "exit\n", 5);
	add_history(line);
	return (line);
}

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	t_token_list	*list;
	t_cmd			*cmd_list;

	(void)argc, (void)argv;
	signal(SIGINT, sigNormal);
	signal(SIGQUIT, sigNormal);
	line = get_line();
	create_my_env(envp);
	g_sigenv.last_status = ft_strdup("0");
	while (line)
	{
		list = tokenize(&line);
		if (list)
		{
			cmd_list = lexer(&list);
			if (cmd_list)
				exec_main(&cmd_list);
		}
		signal(SIGINT, sigNormal);
		signal(SIGQUIT, sigNormal);
		line = get_line();
	}
	delete_env_vbles();
	return (0);
}
