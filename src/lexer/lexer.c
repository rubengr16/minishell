/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 20:08:49 by rgallego          #+#    #+#             */
/*   Updated: 2023/06/29 19:44:41 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>

static t_cmd	*manage_redir(t_cmd *cmd, t_token **token,
	enum e_token_type type)
{
	t_redir	**chosen_redir;
	
	*token = (*token)->next;
	if (!*token)
		return (mini_error(UNEXPECTED_TK, "newline"));
	if (get_token_type((*token)->token, (*token)->context) != OTHER)
		return (mini_error(UNEXPECTED_TK, (*token)->token));
	if (type == R_IN || type == R_IN_HERE_DOC)
		chosen_redir = &cmd->r_in;
	else
		chosen_redir = &cmd->r_out;
	if (!insert_to_redir_list(chosen_redir, (*token)->token, type))
		return (NULL);
	return (cmd);
}

t_cmd	*manage_other(t_cmd *cmd, t_token **token)
{
	enum e_token_type	type;
	
	if ((*token)->next)
		type = get_token_type((*token)->next->token, (*token)->next->context);
	else
		type = OTHER;
	if ((type == OTHER || type == PIPE) && cmd->cmd)
	{
		if (!add_to_char_double_ptr(&cmd->args, (*token)->token))
			return (NULL);
		return (cmd);
	}
	else if (type == OTHER || type == PIPE)
	{
		cmd->cmd = (*token)->token;
		return (cmd);
	}
	return (cmd);
}

t_cmd	*lexer(t_token_list **token_list)
{
	t_cmd				*cmd_list;
	t_cmd				*cmd;
	t_token				*token;
	enum e_token_type	type;

	cmd_list = NULL;
	token = (*token_list)->start;
	cmd = new_cmd();
	while (token && cmd)
	{
		type = get_token_type(token->token, token->context);
		while (token && cmd)
		{
			if (type == OTHER)
				cmd = manage_other(cmd, &token);
			if (type == R_IN || type == R_IN_HERE_DOC 
				|| type == R_OUT || type == R_OUT_APPEND)
				cmd = manage_redir(cmd, &token, type);
			token = token->next;
			if (token)
				type = get_token_type(token->token, token->context);
		}
		if (cmd)
			add_to_cmd_list(&cmd_list, cmd);
		// if (cmd && !cmd->cmd)
		// 	cmd = mini_error(UNEXPECTED_TK, "|");
		if (cmd)
			cmd = new_cmd();
	}
	if (!cmd)
	{
		delete_token_list(token_list, 0);
		delete_cmd_list(&cmd_list);
		return (NULL);
	}
	return (cmd_list);
}
