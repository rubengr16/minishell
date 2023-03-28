/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlist.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 10:19:13 by rgallego          #+#    #+#             */
/*   Updated: 2022/09/26 11:00:13 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDLIST_H
# define CMDLIST_H

# include <stdlib.h>
# include "libft.h"

/*************************** COMMAND STRUCTURE ****************************** */
# define CMD 0

/************************** CMDLIST STRUCTURE ****************************** */
typedef struct s_node
{
	char			**cmd_flag;
	struct s_node	*next;
}	t_node;

typedef struct s_cmdlist
{
	int		n_elem;
	t_node	*head;
	t_node	*tail;
}	t_cmdlist;

/************************** CMDLIST FUNCTIONS ****************************** */
t_cmdlist	*cmdlistinit(void);
t_node		*newnode(char **cmd_flag);
void		cmdlistpush(t_cmdlist *list, t_node *node);
t_node		*cmdlistpush_cmd(t_cmdlist *list, char **cmd_flag);
t_node		*cmdlistpop(t_cmdlist *list);
void		cmdlistdelone(t_cmdlist *list);
void		cmdlistdelall(t_cmdlist *list);

#endif
