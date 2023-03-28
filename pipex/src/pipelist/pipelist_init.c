/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelist_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 10:18:45 by rgallego          #+#    #+#             */
/*   Updated: 2022/09/26 10:58:22 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipelist.h"

t_pipelist	*pipelistinit(void)
{
	t_pipelist	*list;

	list = malloc(sizeof(t_pipelist));
	if (!list)
		return (NULL);
	list->n_elem = 0;
	list->head = NULL;
	list->tail = NULL;
	return (list);
}

t_pipelist	*pipelistinitpush(int n)
{
	t_pipelist	*list;

	list = pipelistinit();
	while (list && list->n_elem < n)
	{
		if (!pipelistpush(list))
			pipelistdelall(list);
	}
	return (list);
}
