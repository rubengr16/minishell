/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:48:06 by rgallego          #+#    #+#             */
/*   Updated: 2023/06/30 00:21:15 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include "executtor.h"

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

void	create_command(t_cmd **command)	// Auxiliar hasta que este el parser
{
	t_cmd	*cmd1;
	t_cmd	*cmd2;

	cmd1 = malloc(sizeof(t_cmd));
	cmd1->cmd = ft_strdup("ls");
	cmd1->args = malloc(sizeof(char *) * 3);
	cmd1->args[0] = ft_strdup("ls");
	cmd1->args[1] = ft_strdup("-l");
	cmd1->args[2] = NULL;
	cmd1->r_out = NULL;
	cmd1->r_in = NULL;

	cmd2 = malloc(sizeof(t_cmd));
	cmd2->cmd = ft_strdup("wc");
	cmd2->args = malloc(sizeof(char *) * 3);
	cmd2->args[0] = ft_strdup("wc");
	cmd2->args[1] = ft_strdup("-l");
	cmd2->args[2] = NULL;
	cmd2->next = NULL;
	cmd2->r_out = NULL;
	cmd2->r_in = NULL;

	cmd1->next = cmd2;
	*command = cmd1;
}

/*int argc, char **argv, char **env*/
int	main(int argc, char **argv, char **envp)
{
	char			*line;
	t_token_list	*list;
	t_cmd			*cmd_list;
	t_enviroment	*my_env = malloc(sizeof(t_enviroment));
	if (!my_env)
		return (1);
	
	(void)argc;
	(void)argv;
	create_command(&cmd_list);
	create_env_list(envp, my_env);
	exec_main(cmd_list, my_env);
	delete_cmd_list(&cmd_list);
	delete_env_variables(my_env);
	return 0;
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
	
}
