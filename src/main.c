/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: socana-b <socana-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:48:06 by rgallego          #+#    #+#             */
/*   Updated: 2023/07/18 20:24:20 by socana-b         ###   ########.fr       */
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
/*
t_cmd	*cmd1;

cmd1 = malloc(sizeof(t_cmd));
cmd1->cmd = ft_strdup("cat");
cmd1->args = malloc(sizeof(char *) * 2);
cmd1->args[0] = ft_strdup("cat");
cmd1->args[1] = NULL;
cmd1->r_out = NULL;
cmd1->r_in = files_in;

t_redir *files_in = malloc(sizeof(t_redir));

files_in->file = ft_strdup("EOL");
files_in->type = R_IN_HERE_DOC;
files_in->next = NULL;

*/
void	create_command(t_cmd **command)	// Auxiliar hasta que este el parser
{
	t_cmd	*cmd1;
//	t_cmd	*cmd2;
//	t_cmd	*cmd3;

	t_redir *files_in = malloc(sizeof(t_redir));
	files_in->file = ft_strdup("EOL");
	files_in->type = R_IN_HERE_DOC;
	files_in->next = NULL;

	cmd1 = malloc(sizeof(t_cmd));
	cmd1->cmd = ft_strdup("sort");
	cmd1->args = malloc(sizeof(char *) * 2);
	cmd1->args[0] = ft_strdup("sort");
	cmd1->args[1] = NULL;
	cmd1->r_out = NULL;
	cmd1->r_in = files_in;
/*
	cmd2 = malloc(sizeof(t_cmd));
	cmd2->cmd = ft_strdup("pwd");
	cmd2->args = malloc(sizeof(char *) * 2);
	cmd2->args[0] = ft_strdup("pwd");
	cmd2->args[1] = NULL;
	cmd2->r_out = NULL;
	cmd2->r_in = NULL;

	cmd3 = malloc(sizeof(t_cmd));
	cmd3->cmd = ft_strdup("ls");
	cmd3->args = malloc(sizeof(char *) * 2);
	cmd3->args[0] = ft_strdup("ls");
	cmd3->args[1] = NULL;
	cmd3->r_out = NULL;
	cmd3->r_in = NULL;
*/
	cmd1->next = NULL;
//	cmd2->next = NULL;
//	cmd3->next = NULL;
	*command = cmd1;
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
	signal(SIGINT, signalHandling);
	signal(SIGQUIT, signalHandling);
	line = get_line();
	while (line)
	{
		if (line && *line)
		{
			list = tokenize(&line);
			if (!list)
				return (1);
			cmd_list = lexer(&list);
			if (!cmd_list)
				return (1);
			create_env_list(envp, my_env);
			exec_main(cmd_list, my_env);
			//print_cmd_list(cmd_list);
			delete_cmd_list(&cmd_list);
		}
		line = get_line();
	}
	delete_env_variables(my_env);
	return (0);
}
