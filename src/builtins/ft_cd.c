/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:23:23 by rgallego          #+#    #+#             */
/*   Updated: 2023/08/17 16:29:26 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	update_pwd(char *prvs_pwd, char *current_pwd)
{
	char	*oldpwd;
	char	*newpwd;

	oldpwd = ft_strjoin("OLDPWD=", prvs_pwd);
	if (!oldpwd)
		return ((void)mini_error("cd", NULL, SYS_ERR, NULL));
	free(prvs_pwd);
	newpwd = ft_strjoin("PWD=", current_pwd);
	if (!newpwd)
		return ((void)mini_error("cd", NULL, SYS_ERR, NULL));
	free(current_pwd);
	set_vble(oldpwd, ft_strchr(oldpwd, '='));
	set_vble(newpwd, ft_strchr(newpwd, '='));
	free(oldpwd);
	free(newpwd);
}

void	change_dir(char *path, char *old)
{
	if (chdir(path))
	{
		mini_error("cd", path, SYS_ERR, old);
		errno = 1;
	}
	else
	{
		update_pwd(old, getcwd(NULL, 0));
		errno = 0;
	}
}

void	ft_cd(char **args)
{
	char	*path;
	char	*old;
	int		len;

	len = len_char_double_ptr(args);
	old = getcwd(NULL, 0);
	if (len == 1)
	{
		path = get_env("HOME");
		if (!path && get_pos_vble("HOME"))
			return ((void)mini_error("cd", NO_HOME_MSG, NO_HOME_ERR, old));
		errno = 0;
	}
	else
		path = args[1];
	change_dir(path, old);
}
