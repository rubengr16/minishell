/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:23:23 by rgallego          #+#    #+#             */
/*   Updated: 2023/07/28 10:37:53 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	update_pwd(void)
{
	char	*new_pwd;
	int		i;

	i = 0;
	new_pwd = ft_strjoin("PWD=", getcwd(NULL, 0));
	if (!new_pwd)
		return ;
	while (ft_strncmp(g_sigenv.envp[i], "PWD=", 4) != 0)
		i++;
	free(g_sigenv.envp[i]);
	g_sigenv.envp[i] = new_pwd;
}

static char	*cd_aux(char **args, int *free_flag)
{
	char	*result;

	if (args[1][0] == '~' && args[1][1] == '\0')
		result = get_env("HOME");
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
	int		free_flag;
	int		result;

	free_flag = 0;
	if (len_char_double_ptr(args) > 2)
	{
		write(2, "cd: too many arguments\n", 23);
		return (1);
	}
	if (len_char_double_ptr(args) == 1)
	{
		complete_path = get_env("HOME");
		if (!complete_path)
		{
			mini_error("cd", NULL, "HOME not set", NULL);
			return (1);
		}
	}
	else
		complete_path = cd_aux(args, &free_flag);
	result = change_dir(complete_path, free_flag);
	update_pwd();
	return (result);
}
