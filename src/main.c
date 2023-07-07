/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:48:06 by rgallego          #+#    #+#             */
/*   Updated: 2023/07/07 19:02:11 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "parser.h"
#include "lexer.h"

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

/*int argc, char **argv, char **env*/
int	main(void)
{
	char			*line;
	t_token_list	*list;
	t_cmd			*cmd_list;

	line = get_line();
	if (line && *line)
	{
		list = tokenize(&line);
		if (!list)
			return (1);
		print_list(list);
		cmd_list = lexer(&list);
		if (!cmd_list)
			return (1);
		print_cmd_list(cmd_list);
		delete_cmd_list(&cmd_list);
	}
	atexit(discover_leaks);
}
