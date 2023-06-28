/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:48:06 by rgallego          #+#    #+#             */
/*   Updated: 2023/06/24 20:07:53 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include "parser.h"

void	discover_leaks(void)
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	t_token_list	*list;

	(void)argc;	// Para anular los warning, no se me ocurre nada mejor
	(void)argv;
	line = readline("minishell> ");
	list = tokenize(&line, envp);
	print_list(list);
	delete_list(list);
	atexit(discover_leaks);
}
