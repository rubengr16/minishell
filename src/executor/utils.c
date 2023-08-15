/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:40:03 by rgallego          #+#    #+#             */
/*   Updated: 2023/08/14 12:44:19 by rgallego         ###   ########.fr       */
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

static char	*ft_strjoinsep(char const *s1, char const *s2, char *c)
{
	int		len;
	char	*s;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 2;
	s = malloc(sizeof(char) * (len));
	if (!s)
		return (NULL);
	(void)ft_strlcpy(s, s1, len);
	(void)ft_strlcat(s, c, len);
	(void)ft_strlcat(s, s2, len);
	return (s);
}

char	*verify_commands(char **path, char *cmd)
{
	char	*command;
	int		i;

	i = 0;
	if (!path)
	{
		mini_error(cmd, CMD_NOT_FOUND_MSG, CMD_NOT_FOUND_ERR, NULL);
		return (NULL);
	}
	if (!access(cmd, X_OK))
		return (cmd);
	command = ft_strjoinsep(path[i], cmd, "/");
	while (path[i] && access(command, F_OK | X_OK))
	{
		i++;
		free(command);
		command = ft_strjoinsep(path[i], cmd, "/");
	}
	if (!path[i] || !path)
	{
		mini_error(cmd, CMD_NOT_FOUND_MSG, CMD_NOT_FOUND_ERR, NULL);
		command = NULL;
	}
	free_double_char_ptr(path);
	return (command);
}
