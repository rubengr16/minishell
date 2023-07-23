/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:11:30 by rgallego          #+#    #+#             */
/*   Updated: 2023/07/24 01:03:21 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enviroment.h"

char	**create_my_env(char **envp)
{
	char			**my_envp;
	unsigned int	i;

	i = 0;
	if (envp)
		while (envp[i])
			i++;
	my_envp = malloc(sizeof(char *) * (i + 1));
	if (!my_envp)
		mini_error(NULL, NULL, ALLOC_ERR, NULL);
	i = 0;
	while (my_envp && envp[i])
	{
		my_envp[i] = ft_strdup(envp[i]);
		if (!my_envp[i])
			delete_env_vbles(&my_envp);
		i++;
	}
	if (my_envp)
		my_envp[i] = NULL;
	return (my_envp);
}

void	delete_env_vbles(char ***my_envp)
{
	unsigned int	i;

	if (!*my_envp)
		return ;
	i = 0;
	while ((*my_envp)[i])
	{
		free((*my_envp)[i]);
		i++;
	}
	free(*my_envp);
	*my_envp = NULL;
}

 int	get_pos_vble(char **my_envp, char *name)
{
	unsigned int	i;
	int	pos;

	if (!my_envp)
		return (-1);
	i = 0;
	pos = -1;
	while (pos < 0 && my_envp[i])
	{
		if (ft_strncmp(my_envp[i], name, (ft_strlen(name) + 1)) == '=')
			pos = i;
		i++;
	}
	if (!my_envp[i])
		return (-1);
	return (pos);
}

char	*get_env(char **my_envp, char *name)
{
	int				pos;

	pos = get_pos_vble(my_envp, name);
	if (pos < 0)
		return (NULL);
	return (ft_strchr(my_envp[pos], '=') + 1);
}

void	ft_env(char **my_envp)
{
	unsigned int	i;

	if (!my_envp)
		return ;
	i = 0;
	while (my_envp[i])
	{
		ft_putendl_fd(my_envp[i], STDOUT_FILENO);
		i++;
	}
}
