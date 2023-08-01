/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: socana-b <socana-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:23:23 by rgallego          #+#    #+#             */
/*   Updated: 2023/08/01 18:33:48 by socana-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	update_pwd(char *oldpwd)
{
	char	**new_pwd;
	char	**old_pwd;
	
	new_pwd = malloc(sizeof(char *) * 3);
	old_pwd = malloc(sizeof(char *) * 3);
	if (!new_pwd)
		return ;
	new_pwd[0] = ft_strdup("export");
	old_pwd[0] = ft_strdup("export");
	if (!new_pwd[0] || !old_pwd[0])
		return ;
	old_pwd[1] = ft_strjoin("OLDPWD=", oldpwd);
	new_pwd[1] = ft_strjoin("PWD=", getcwd(NULL, 0));
	if (!new_pwd[1] || !old_pwd[1])
		return ;
	new_pwd[2] = NULL;
	old_pwd[2] = NULL;
	ft_export(new_pwd);
	ft_export(old_pwd);
}

static char	*cd_aux(char **args, int *free_flag)
{
	char	*result;

	if (args[1][0] == '-' && args[1][1] == '\0')
	{
		result = get_env("OLDPWD");
		if (!result)
			mini_error("cd", NULL, "OLDPWD not set", NULL);
	}
	else if (args[1][0] == '~' && args[1][1] == '\0')
	{
		result = get_env("HOME");
		if (!result)
			mini_error("cd", NULL, "HOME not set", NULL);
	}
	else if (args[1][0] == '~' && args[1][1] == '/')
	{
		result = ft_strjoin(get_env("HOME"), (args[1] + 1));
		if (!result)
			return(NULL);
		*free_flag = 1;
	}
	else
		result = args[1];
	return (result);
}

static int	change_dir(char *complete_path, int free_flag)
{
	if (!complete_path)
		return (1);
	if (chdir(complete_path))
	{
		mini_error("cd", complete_path, "No such file or directory", NULL);
		if (free_flag)
			free(complete_path);
		return (1);
	}
	if (free_flag)
		free(complete_path);
	return (0);
}

int	ft_cd(char **args)
{
	char	*complete_path;
	char	*old;
	int		free_flag;
	int		result;

	free_flag = 0;
	old = getcwd(NULL, 0);
	if (len_char_double_ptr(args) > 2)
	{
		write(2, "cd: too many arguments\n", 23);
		return (1);
	}
	if (len_char_double_ptr(args) == 1)
	{
		complete_path = get_env("HOME");
		if (!complete_path)
			mini_error("cd", NULL, "HOME not set", NULL);
	}
	else
		complete_path = cd_aux(args, &free_flag);
	result = change_dir(complete_path, free_flag);
	if (result == 0)
		update_pwd(old);
	return (result);
}
