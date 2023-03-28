/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlist_push.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 10:45:37 by rgallego          #+#    #+#             */
/*   Updated: 2022/09/21 22:15:17 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmdlist.h"

t_node	*newnode(char **cmd_flag)
{
	t_node	*aux;

	aux = malloc(sizeof(t_node));
	if (!aux)
		return (NULL);
	aux->cmd_flag = cmd_flag;
	aux->next = NULL;
	return (aux);
}

void	cmdlistpush(t_cmdlist *list, t_node *node)
{
	if (!node)
		return ;
	if (!list->n_elem)
		list->head = node;
	else
		list->tail->next = node;
	list->tail = node;
	list->n_elem++;
}

t_node	*cmdlistpush_cmd(t_cmdlist *list, char **cmd_flag)
{
	t_node	*aux;

	aux = newnode(cmd_flag);
	if (!aux)
		return (NULL);
	cmdlistpush(list, aux);
	return (aux);
}
