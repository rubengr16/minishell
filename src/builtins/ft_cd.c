/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: socana-b <socana-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:23:23 by rgallego          #+#    #+#             */
/*   Updated: 2023/08/02 18:23:34 by socana-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	update_pwd(char *prvs_pwd, char *current_pwd)
{
	char	*newpwd;
	char	*oldpwd;
	
	oldpwd = ft_strjoin("OLDPWD=", prvs_pwd);
	if (!oldpwd)
		return ((void)mini_error("cd", NULL, ALLOC_ERR, NULL));
	newpwd = ft_strjoin("PWD=", current_pwd);
	if (!newpwd)
		return ((void)mini_error("cd", NULL, ALLOC_ERR, NULL));
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
		mini_error("cd", path, strerror(errno), NULL);
		return (1);
	}
	update_pwd(old, getcwd(NULL, 0));
	return (0);
}
