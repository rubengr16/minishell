/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 20:08:49 by rgallego          #+#    #+#             */
/*   Updated: 2023/08/14 12:40:19 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_cmd	*manage_redir(t_cmd *cmd, t_token **token,
	enum e_token_type type)
{
	char	*real_token;

	*token = (*token)->next;
	if (!*token)
		return (mini_error(UNEXPECTED_TK_MSG, "newline", SYS_ERR, NULL));
	if (get_token_type((*token)->token) != OTHER)
		return (mini_error(UNEXPECTED_TK_MSG, (*token)->token, SYS_ERR, NULL));
	real_token = get_real_token((*token)->token, 1);
	if (!real_token)
		return (NULL);
	if (!insert_to_redir_list(&cmd->redir, real_token, type))
		return (NULL);
	return (cmd);
}

t_cmd	*manage_other(t_cmd *cmd, t_token **token)
{
	char	**splitted_token;
	char	*real_token;
	int		i;

	real_token = get_real_token((*token)->token, 0);
	if (!real_token)
		return (NULL);
	splitted_token = ft_split(real_token, TRANS_VBLE_SPACE);
	if (!splitted_token && ft_strlen(real_token))
		return (mini_error(NULL, NULL, SYS_ERR, real_token));
	free(real_token);
	i = 0;
	if (!cmd->cmd)
		cmd->cmd = splitted_token[i];
	while (0 <= i && splitted_token[i])
	{
		if (!add_to_char_double_ptr(&cmd->args, splitted_token[i]))
			i = -2;
		i++;
	}
	free(splitted_token);
	if (i < 0)
		return (NULL);
	return (cmd);
}

t_cmd	*manage_pipe(t_cmd *cmd_list, t_cmd *cmd, t_token **token)
{
	if (cmd_list == cmd && !cmd->cmd && !cmd->args && !cmd->redir)
		return (mini_error(UNEXPECTED_TK_MSG, (*token)->token, SYNTAX_ERR,
				NULL));
	*token = (*token)->next;
	if (*token && get_token_type((*token)->token) == PIPE)
		return (mini_error(UNEXPECTED_TK_MSG, (*token)->token, SYNTAX_ERR,
				NULL));
	return (cmd);
}

t_cmd	*get_cmd(t_cmd **cmd_list, t_cmd *cmd, t_token **token)
{
	enum e_token_type	type;

	type = get_token_type((*token)->token);
	while (*token && cmd && type != PIPE)
	{
		if (type == OTHER)
			cmd = manage_other(cmd, token);
		if (type == R_IN || type == R_IN_HERE_DOC
			|| type == R_OUT || type == R_OUT_APPEND)
			cmd = manage_redir(cmd, token, type);
		if (cmd)
			*token = (*token)->next;
		if (*token)
			type = get_token_type((*token)->token);
	}
	if (type == PIPE)
		cmd = manage_pipe(*cmd_list, cmd, token);
	if (cmd && *token)
		cmd = add_to_cmd_list(cmd_list);
	return (cmd);
}

t_cmd	*lexer(t_token_list **token_list)
{
	t_cmd	*cmd_list;
	t_cmd	*cmd;
	t_token	*token;

	cmd_list = NULL;
	token = (*token_list)->start;
	cmd = add_to_cmd_list(&cmd_list);
	while (token && cmd)
		cmd = get_cmd(&cmd_list, cmd, &token);
	delete_token_list(token_list);
	if (!cmd)
	{
		delete_cmd_list(&cmd_list);
		return (NULL);
	}
	return (cmd_list);
}
