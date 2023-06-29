/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 20:08:49 by rgallego          #+#    #+#             */
/*   Updated: 2023/06/29 21:10:51 by rgallego         ###   ########.fr       */
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
	if (!cmd->cmd)
	{
		cmd->cmd = (*token)->token;
		return (cmd);
	}
	if (!add_to_char_double_ptr(&cmd->args, (*token)->token))
		return (NULL);
	return (cmd);
}

t_cmd	*manage_pipe(t_cmd *cmd_list, t_cmd *cmd, t_token **token)
{
	if (cmd_list == cmd 
		&& !cmd->cmd && !cmd->args && !cmd->r_in && !cmd->r_out)
		return (mini_error(UNEXPECTED_TK, (*token)->token));
	*token = (*token)->next;
	if (!*token)
		return mini_error(UNEXPECTED_TK, "newline"); // In doubt
	if (*token && get_token_type((*token)->token, (*token)->context) == PIPE)
		return (mini_error(UNEXPECTED_TK, (*token)->token));
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
	cmd = add_to_cmd_list(&cmd_list);
	while (token && cmd)
	{
		type = get_token_type(token->token, token->context);
		while (token && cmd && type != PIPE)
		{
			if (type == OTHER)
				cmd = manage_other(cmd, &token);
			if (type == R_IN || type == R_IN_HERE_DOC 
				|| type == R_OUT || type == R_OUT_APPEND)
				cmd = manage_redir(cmd, &token, type);
			if (cmd)
				token = token->next;
			if (token)
				type = get_token_type(token->token, token->context);
		}
		if (type == PIPE)
			cmd = manage_pipe(cmd_list, cmd, &token);
		if (cmd && token)
			cmd = add_to_cmd_list(&cmd_list);
	}
	if (!cmd)
	{
		delete_token_list(token_list, 0);
		delete_cmd_list(&cmd_list);
		return (NULL);
	}
	delete_token_list(token_list, 0);
	return (cmd_list);
}
