/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 20:08:49 by rgallego          #+#    #+#             */
/*   Updated: 2023/07/20 23:23:19 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_cmd	*manage_redir(t_cmd *cmd, t_token **token,
	enum e_token_type type)
{
	t_redir	**chosen_redir;
	char	*real_token;

	*token = (*token)->next;
	if (!*token)
		return (mini_error(UNEXPECTED_TK, "newline", NULL));
	if (get_token_type((*token)->token) != OTHER)
		return (mini_error(UNEXPECTED_TK, (*token)->token, NULL));
	if (type == R_IN || type == R_IN_HERE_DOC)
		chosen_redir = &cmd->r_in;
	else
		chosen_redir = &cmd->r_out;
	real_token = get_real_token((*token)->token, 1);
	if (!real_token)
		return (NULL);
	if (!insert_to_redir_list(chosen_redir, real_token, type))
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
		return (mini_error(NULL, SPLIT_ERR, real_token));
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
	if (i == -1)
		return (NULL);
	return (cmd);
}

t_cmd	*manage_pipe(t_cmd *cmd_list, t_cmd *cmd, t_token **token)
{
	if (cmd_list == cmd
		&& !cmd->cmd && !cmd->args && !cmd->r_in && !cmd->r_out)
		return (mini_error(UNEXPECTED_TK, (*token)->token, NULL));
	*token = (*token)->next;
	if (*token && get_token_type((*token)->token) == PIPE)
		return (mini_error(UNEXPECTED_TK, (*token)->token, NULL));
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
	if (!cmd)
	{
		delete_token_list(token_list);
		delete_cmd_list(&cmd_list);
		return (NULL);
	}
	delete_token_list(token_list);
	return (cmd_list);
}
