/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:48:06 by rgallego          #+#    #+#             */
/*   Updated: 2023/06/29 19:10:35 by rgallego         ###   ########.fr       */
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

/*int argc, char **argv, char **env*/
int	main(void)
{
	char			*line;
	t_token_list	*list;
	t_cmd			*cmd_list;

	line = readline("minishell> ");
	list = tokenize(&line);
	if (!list)
		return (1);
	print_list(list);
	cmd_list = lexer(&list);
	if (!cmd_list)
		return (1);
	print_cmd_list(cmd_list);
	delete_token_list(&list, 0);
	delete_cmd_list(&cmd_list);
	atexit(discover_leaks);
}
