/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:40:03 by rgallego          #+#    #+#             */
/*   Updated: 2023/08/16 13:36:52 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	count_cmds(t_cmd *cmd_list)
{
	t_cmd	*aux;
	int		i;

	i = 0;
	aux = cmd_list;
	while (aux)
	{
		i++;
		aux = aux->next;
	}
	return (i);
}

int	is_builtin(char *cmd)
{
	return (cmd && (!ft_strncmp(cmd, "echo", 5) || !ft_strncmp(cmd, "pwd", 4)
			|| !ft_strncmp(cmd, "export", 7) || !ft_strncmp(cmd, "unset", 6)
			|| !ft_strncmp(cmd, "env", 4) || (!ft_strncmp(cmd, "exit", 5)
				|| !ft_strncmp(cmd, "cd", 3))));
}

int	is_builtin_on_parent(t_cmd	*cmd)
{
	return (cmd->cmd && !cmd->next && (!ft_strncmp(cmd->cmd, "export", 7)
			|| !ft_strncmp(cmd->cmd, "cd", 3)
			|| !ft_strncmp(cmd->cmd, "unset", 6)
			|| !ft_strncmp(cmd->cmd, "exit", 5)));
}
