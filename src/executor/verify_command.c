/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: socana-b <socana-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:05:29 by rgallego          #+#    #+#             */
/*   Updated: 2023/08/16 15:04:53 by socana-b         ###   ########.fr       */
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

static int	extensive_command_search(char **path, char **command, char *cmd)
{
	int	cmd_state;
	int	denied;
	int	i;

	*command = cmd;
	cmd_state = exists_and_exec(*command);
	printf("First OK\n");
	if (cmd_state == OK)
		return (cmd_state);
	else if (cmd_state == EXEC_DENIED)
		denied = EXEC_DENIED;
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
	printf("Denied\n");
	if (cmd_state != OK && (cmd_state == EXEC_DENIED || denied == EXEC_DENIED))
		return (EXEC_DENIED);
	printf("OK\n");
	return (cmd_state);
}

char	*verify_commands(char **path, char *cmd)
{
	char	*command;
	int		is_executable;

	if (!path || !*cmd)
	{
		mini_error(cmd, CMD_NOT_FOUND_MSG, CMD_NOT_FOUND_ERR, NULL);
		return (NULL);
	}
	is_executable = extensive_command_search(path, &command, cmd);
	if (is_executable == NOT_FOUND || is_executable == EXEC_DENIED)
	{
		command = NULL;
		if (is_executable == NOT_FOUND)
			(void)mini_error(cmd, CMD_NOT_FOUND_MSG, CMD_NOT_FOUND_ERR, NULL);
		else if (is_executable == EXEC_DENIED)
			(void)mini_error(cmd, EXEC_DENIED_MSG, EXEC_DENIED_ERR, NULL);
	}
	(void)free_double_char_ptr(path);
	return (command);
}
