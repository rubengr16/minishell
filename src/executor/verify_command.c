/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:05:29 by rgallego          #+#    #+#             */
/*   Updated: 2023/08/21 17:11:15 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	exists_and_exec(char *cmd)
{
	if (access(cmd, F_OK))
		return (NOT_FOUND);
	else if (access(cmd, X_OK))
		return (EXEC_DENIED);
	return (OK);
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

static int	extensive_command_search(char **path, char **command, char *cmd,
	int cmd_state)
{
	int	denied;
	int	i;

	*command = cmd;
	i = 0;
	*command = ft_strjoinsep(path[i], cmd, "/");
	cmd_state = exists_and_exec(*command);
	while (path[i] && cmd_state != OK)
	{
		if (cmd_state == EXEC_DENIED)
			denied = EXEC_DENIED;
		i++;
		free(*command);
		*command = ft_strjoinsep(path[i], cmd, "/");
		cmd_state = exists_and_exec(*command);
	}
	if (cmd_state != OK && (cmd_state == EXEC_DENIED || denied == EXEC_DENIED))
		return (EXEC_DENIED);
	return (cmd_state);
}

char	*verify_commands(char **path, char *cmd)
{
	char	*command;
	int		is_executable;

	if (!*cmd)
		return (mini_error(cmd, CMD_NOT_FOUND_MSG, CMD_NOT_FOUND_ERR, NULL));
	if (ft_strncmp(cmd, "./", 2) == 0 || ft_strncmp(cmd, "../", 3) == 0
		|| *cmd == '/')
	{
		(void)free_double_char_ptr(path);
		if (exists_and_exec(cmd) == OK)
			return (cmd);
		if (exists_and_exec(cmd) == EXEC_DENIED)
			return (mini_error(cmd, EXEC_DENIED_MSG, EXEC_DENIED_ERR, NULL));
		return (mini_error(cmd, NOT_FILE_DIR, CMD_NOT_FOUND_ERR, NULL));
	}
	if (!path)
		return (mini_error(cmd, CMD_NOT_FOUND_MSG, CMD_NOT_FOUND_ERR, NULL));
	is_executable = extensive_command_search(path, &command, cmd, 0);
	(void)free_double_char_ptr(path);
	if (is_executable == NOT_FOUND)
		return (mini_error(cmd, CMD_NOT_FOUND_MSG, CMD_NOT_FOUND_ERR, NULL));
	if (is_executable == EXEC_DENIED)
		return (mini_error(cmd, EXEC_DENIED_MSG, EXEC_DENIED_ERR, NULL));
	return (command);
}
