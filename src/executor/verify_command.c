/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:05:29 by rgallego          #+#    #+#             */
/*   Updated: 2023/09/07 18:19:52 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	exists_and_exec(char *cmd)
{
	if (access(cmd, F_OK))
		return (NOT_FOUND);
	else if (access(cmd, X_OK))
		return (EXEC_DENIED);
	return (OK);
}

static int	extensive_command_search(char **path, char **command, char *cmd,
	int cmd_state)
{
	int	denied;
	int	i;

	if (!*cmd)
		return (NOT_FOUND);
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

static char	*pointed_command(char **path, char *cmd)
{
	DIR	*dir_desc;

	(void)free_double_char_ptr(path);
	if (!ft_strncmp(cmd, "./", 2) || !ft_strncmp(cmd, "../", 3) || *cmd == '/')
	{
		dir_desc = opendir(cmd);
		if (dir_desc)
		{
			closedir(dir_desc);
			return (mini_error(cmd, IS_DIR_MSG, IS_DIR_ERR, NULL));
		}
		if (exists_and_exec(cmd) == OK)
			return (cmd);
		if (exists_and_exec(cmd) == EXEC_DENIED)
			return (mini_error(cmd, EXEC_DENIED_MSG, EXEC_DENIED_ERR, NULL));
		return (mini_error(cmd, NOT_FILE_DIR, CMD_NOT_FOUND_ERR, NULL));
	}
	if (!ft_strncmp(cmd, "..", 2))
		return (mini_error(cmd, CMD_NOT_FOUND_MSG, CMD_NOT_FOUND_ERR, NULL));
	(void)mini_error(cmd, FILE_ARG_REQ_MSG, FILE_ARG_REQ_ERR, NULL);
	ft_putendl_fd(FILE_ARG_REQ_2_MSG, STDERR_FILENO);
	return (NULL);
}

static char	*relative_tranform(char **path, char *cmd)
{
	int	cmd_status;

	(void)free_double_char_ptr(path);
	cmd = ft_strjoin("./", cmd);
	if (!cmd)
		return (mini_error(NULL, NULL, SYS_ERR, NULL));
	cmd_status = exists_and_exec(cmd);
	if (cmd_status == OK)
		return (cmd);
	if (cmd_status == EXEC_DENIED)
		return (mini_error(cmd, EXEC_DENIED_MSG, EXEC_DENIED_ERR, NULL));
	return (mini_error(cmd, NOT_FILE_DIR, CMD_NOT_FOUND_ERR, NULL));
}

char	*verify_command(char **path, char *cmd)
{
	char	*command;
	int		is_executable;

	if (!ft_strncmp(cmd, "./", 2) || !ft_strncmp(cmd, "../", 3) || *cmd == '/'
		|| !ft_strncmp(cmd, ".", 2) || !ft_strncmp(cmd, "..", 3))
		return (pointed_command(path, cmd));
	if (ft_strchr(cmd, '/'))
		return (relative_tranform(path, cmd));
	if (!path)
		return (mini_error(cmd, CMD_NOT_FOUND_MSG, CMD_NOT_FOUND_ERR, NULL));
	is_executable = extensive_command_search(path, &command, cmd, 0);
	(void)free_double_char_ptr(path);
	if (!*cmd)
		return (mini_error(cmd, CMD_NOT_FOUND_MSG, CMD_NOT_FOUND_ERR, NULL));
	if (is_executable == NOT_FOUND)
		return (mini_error(cmd, CMD_NOT_FOUND_MSG, CMD_NOT_FOUND_ERR, NULL));
	if (is_executable == EXEC_DENIED)
		return (mini_error(cmd, EXEC_DENIED_MSG, EXEC_DENIED_ERR, NULL));
	return (command);
}
