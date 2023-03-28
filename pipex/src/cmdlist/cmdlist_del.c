/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlist_del.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:10:37 by rgallego          #+#    #+#             */
/*   Updated: 2022/09/21 22:14:28 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmdlist.h"

void	cmdlistdelone(t_cmdlist *list)
{
	t_node	*aux;

	if (!list->n_elem)
		return ;
	aux = cmdlistpop(list);
	ft_free_split(aux->cmd_flag);
	free(aux);
}

void	cmdlistdelall(t_cmdlist *list)
{
	if (!list)
		return ;
	while (list->n_elem)
		cmdlistdelone(list);
	list->head = NULL;
	list->tail = NULL;
	free(list);
	list = NULL;
}
