/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelist_del.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:10:37 by rgallego          #+#    #+#             */
/*   Updated: 2022/09/26 11:01:39 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipelist.h"

void	pipelistdelone(t_pipelist *list)
{
	t_pipe	*aux;

	if (!list)
		return ;
	aux = pipelistpop(list);
	free(aux);
}

void	pipelistdelall(t_pipelist *list)
{
	if (!list)
		return ;
	while (list->n_elem)
		pipelistdelone(list);
	list->head = NULL;
	list->tail = NULL;
	free(list);
	list = NULL;
}
