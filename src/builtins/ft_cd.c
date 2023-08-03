/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:23:23 by rgallego          #+#    #+#             */
/*   Updated: 2023/08/03 18:25:19 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	update_pwd(char *prvs_pwd, char *current_pwd)
{
	char	*oldpwd;
	char	*newpwd;

	oldpwd = ft_strjoin("OLDPWD=", prvs_pwd);
	if (!oldpwd)
		return ((void)mini_error("cd", NULL, ALLOC_ERR, NULL));
	free(prvs_pwd);
	newpwd = ft_strjoin("PWD=", current_pwd);
	if (!newpwd)
		return ((void)mini_error("cd", NULL, ALLOC_ERR, NULL));
	free(current_pwd);
	set_vble(oldpwd, ft_strchr(oldpwd, '='));
	set_vble(newpwd, ft_strchr(newpwd, '='));
	free(oldpwd);
	free(newpwd);
}

int	ft_cd(char **args)
{
	char	*path;
	char	*old;
	int		len;

	len = len_char_double_ptr(args);
	old = getcwd(NULL, 0);
	if (len > 2)
	{
		write(2, "cd: too many arguments\n", 23);
		return (1);
	}
	if (len == 1)
	{
		path = get_env("HOME");
		if (!path)
		{
			mini_error("cd", NULL, "HOME not set", NULL);
			return (1);
		}
	}
	else
		path = args[1];
	if (chdir(path))
	{
		mini_error("cd", path, strerror(errno), old);
		errno = 1;
	}
	else
	{
		update_pwd(old, getcwd(NULL, 0));
		errno = 0;
	}
	return (errno);
}
