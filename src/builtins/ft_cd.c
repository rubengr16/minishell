/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:23:23 by rgallego          #+#    #+#             */
/*   Updated: 2023/07/24 09:50:18 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static char	*cd_aux(char **args, int *free_flag)
{
	char	*result;

	*free_flag = 0;
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


void	ft_cd(char **args)
{
	char	*complete_path;
	int		free_flag;

	if (len_char_double_ptr(args) == 1)
	{
		complete_path = get_env("HOME");
		if (!complete_path)
			return (void)mini_error("cd", NULL, "HOME not set", NULL);
		if (chdir(complete_path))
			return (void)mini_error("cd", complete_path, "No such file or directory", NULL);
	}
	else if (len_char_double_ptr(args) == 1)
	{
		complete_path = cd_aux(args, &free_flag);
		if (chdir(complete_path))
			printf("cd: %s: No such file or directory\n", args[1]);
		if (free_flag)
			free(complete_path);
	}
	else
		write(2, "cd: too many arguments\n", 23);
}
