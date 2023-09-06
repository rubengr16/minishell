/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 22:10:25 by rgallego          #+#    #+#             */
/*   Updated: 2023/09/06 13:32:42 by rgallego         ###   ########.fr       */
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
		if (aux->args)
			(void)free_double_char_ptr(aux->args);
		if (aux->redir)
			delete_redir_list(&aux->redir);
		if (aux->fd_in != STDIN_FILENO)
			close(aux->fd_in);
		if (aux->fd_out != STDOUT_FILENO)
			close(aux->fd_out);
		free(aux);
		aux = *list;
	}
	*list = NULL;
}
