/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: socana-b <socana-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 22:10:25 by rgallego          #+#    #+#             */
/*   Updated: 2023/08/16 18:36:59 by socana-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>

t_cmd	*new_cmd(void)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (mini_error(NULL, NULL, SYS_ERR, NULL));
	new_cmd->cmd = NULL;
	new_cmd->args = NULL;
	new_cmd->redir = NULL;
	new_cmd->fd_in = STDIN_FILENO;
	new_cmd->fd_out = STDOUT_FILENO;
	new_cmd->next = NULL;
	return (new_cmd);
}

t_cmd	*add_to_cmd_list(t_cmd **list)
{
	t_cmd	*aux;
	t_cmd	*cmd;

	cmd = new_cmd();
	if (!cmd)
		return (NULL);
	if (!*list)
		*list = cmd;
	else
	{
		aux = *list;
		while (aux->next)
			aux = aux->next;
		aux->next = cmd;
	}
	return (cmd);
}

void	delete_cmd_list(t_cmd **list)
{
	t_cmd	*aux;

	if (!list || !*list)
		return ;
	aux = *list;
	while (aux)
	{
		*list = (*list)->next;
		if (aux->cmd)
			free(aux->cmd);
		if (aux->args)
			(void)free_double_char_ptr(aux->args);
		if (aux->redir)
			delete_redir_list(&aux->redir);
		free(aux);
		aux = *list;
	}
	*list = NULL;
}

void	print_cmd_list(t_cmd *list)
{
	t_cmd			*aux;
	t_redir			*redir_aux;
	unsigned int	i;

	aux = list;
	while (aux)
	{
		printf("##############################\n");
		printf("- cmd: %s\n", aux->cmd);
		printf("------------------------------\n");
		i = 0;
		while (aux->args && aux->args[i])
		{
			if (!i)
				printf("- args: = %s\n", aux->args[i]);
			else
				printf("         = %s\n", aux->args[i]);
			i++;
		}
		printf("------------------------------\n");
		redir_aux = aux->redir;
		if (redir_aux)
		{
			printf("- redir: = (file: %s, type: %d)\n", redir_aux->file, redir_aux->type);
			redir_aux = redir_aux->next;
			while (redir_aux)
			{
				printf("         (file: %s, type: %d)\n", redir_aux->file, redir_aux->type);
				redir_aux = redir_aux->next;
			}
		}
		printf("\n\n");
		aux = aux->next;
	}
}
