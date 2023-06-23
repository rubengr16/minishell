/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:48:06 by rgallego          #+#    #+#             */
/*   Updated: 2023/06/23 18:48:47 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "parser.h"

void	discover_leaks(void)
{
	system("leaks minishell");
}

/*int argc, char **argv, char **env*/
int	main(void)
{
	char			*line;
	t_token_list	*list;

	line = readline("minishell> ");
	list = tokenize(&line);
	print_list(list);
	delete_list(list);
	atexit(discover_leaks);
}
