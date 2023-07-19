/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 22:10:25 by rgallego          #+#    #+#             */
/*   Updated: 2023/07/19 16:47:09 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_redir	*new_redir(char *file, enum e_token_type type)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (mini_error(NULL, ALLOC_ERR, NULL));
	redir->file = file;
	redir->type = type;
	redir->next = NULL;
	return (redir);
}

t_redir	*insert_to_redir_list(t_redir **list, char *file,
	enum e_token_type type)
{
	t_redir	*aux;
	t_redir	*redir;

	redir = new_redir(file, type);
	if (!redir)
		return (NULL);
	if (!*list)
		*list = redir;
	else
	{
		aux = *list;
		while (aux->next)
			aux = aux->next;
		aux->next = redir;
	}
	return (redir);
}

void	delete_redir_list(t_redir **list)
{
	t_redir	*aux;

	if (!*list)
		return ;
	aux = *list;
	while (aux)
	{
		*list = (*list)->next;
		if (aux->file)
			free(aux->file);
		free(aux);
		aux = *list;
	}
	*list = NULL;
}
