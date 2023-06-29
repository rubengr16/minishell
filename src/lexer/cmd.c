/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 22:10:25 by rgallego          #+#    #+#             */
/*   Updated: 2023/06/29 19:53:00 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>

t_cmd	*new_cmd(void)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (mini_error(NULL, ALLOC_ERR));
	new_cmd->cmd = NULL;
	new_cmd->args = NULL;
	new_cmd->r_in = NULL;
	new_cmd->r_out = NULL;
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

	if (!*list)
		return ;
	aux = *list;
	while (aux)
	{
		*list = (*list)->next;
		if (aux->cmd)
			free(aux->cmd);
		if (aux->args)
			free_double_char_ptr(aux->args);
		if (aux->r_in)
			delete_redir_list(&aux->r_in);
		if (aux->r_out)
			delete_redir_list(&aux->r_out);
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
		redir_aux = aux->r_in;
		if (redir_aux)
		{
			printf("- redir_in: = (file: %s, type: %d)\n", redir_aux->file, redir_aux->type);
			redir_aux = redir_aux->next;
			while (redir_aux)
			{
				printf("         (file: %s, type: %d)\n", redir_aux->file, redir_aux->type);
				redir_aux = redir_aux->next;
			}
		}
		printf("------------------------------\n");
		redir_aux = aux->r_out;
		if (redir_aux)
		{
			printf("- redir_out: = (file: %s, type: %d)\n", redir_aux->file, redir_aux->type);
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
