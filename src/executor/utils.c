/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:40:03 by rgallego          #+#    #+#             */
/*   Updated: 2023/07/24 00:49:08 by rgallego         ###   ########.fr       */
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
	return (!ft_strncmp(cmd, "echo", 5) || !ft_strncmp(cmd, "pwd", 4)
		|| !ft_strncmp(cmd, "export", 7) || !ft_strncmp(cmd, "unset", 6)
		|| !ft_strncmp(cmd, "env", 4) || (!ft_strncmp(cmd, "exit", 5)
		|| !ft_strncmp(cmd, "cd", 3)));
}

int	count_builtins(t_cmd *cmd_list)
{
	t_cmd	*aux;
	int		builtin_cnt;
	int		i;

	i = 0;
	builtin_cnt = 0;
	aux = cmd_list;
	while (aux)
	{
		if (is_builtin(aux->cmd))
			builtin_cnt++;
		i++;
		aux = aux->next;
	}
	return (builtin_cnt);
}

char	*verify_commands(char **path, char *cmd)
{
	char	*commnd;
	int		i;
	int		flag;
	char	*aux;

	i = 0;
	flag = 0;
	if (access(cmd, X_OK) == 0)
		return(cmd);
	while (path[i] && !flag)
	{
		aux = ft_strjoin("/", cmd);
		commnd = ft_strjoin(path[i], aux);
		if (!access(commnd,F_OK | X_OK))
			flag++;
		else
			free(commnd);
		i++;
	}
	if (!flag)
		commnd = NULL;
	free(aux);
	return (commnd);
}
