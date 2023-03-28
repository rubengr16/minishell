/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlist_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 10:18:45 by rgallego          #+#    #+#             */
/*   Updated: 2022/09/21 22:14:39 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmdlist.h"

t_cmdlist	*cmdlistinit(void)
{
	t_cmdlist	*list;

	list = malloc(sizeof(t_cmdlist));
	if (!list)
		return (NULL);
	list->n_elem = 0;
	list->head = NULL;
	list->tail = NULL;
	return (list);
}
