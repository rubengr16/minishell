/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:11:30 by rgallego          #+#    #+#             */
/*   Updated: 2023/07/24 14:43:03 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enviroment.h"

char	**create_my_env(char **envp)
{
	unsigned int	i;

	i = 0;
	if (envp)
		while (envp[i])
			i++;
	g_sigenv.envp = malloc(sizeof(char *) * (i + 1));
	if (!g_sigenv.envp)
		mini_error(NULL, NULL, ALLOC_ERR, NULL);
	i = 0;
	while (g_sigenv.envp && envp[i])
	{
		g_sigenv.envp[i] = ft_strdup(envp[i]);
		if (!g_sigenv.envp[i])
			delete_env_vbles();
		i++;
	}
	if (g_sigenv.envp)
		g_sigenv.envp[i] = NULL;
	return (g_sigenv.envp);
}

void	delete_env_vbles(void)
{
	unsigned int	i;

	if (!g_sigenv.envp)
		return ;
	i = 0;
	while (g_sigenv.envp[i])
	{
		free(g_sigenv.envp[i]);
		i++;
	}
	free(g_sigenv.envp);
	g_sigenv.envp = NULL;
}

 int	get_pos_vble(char *name)
{
	unsigned int	i;
	int	pos;

	if (!g_sigenv.envp)
		return (-1);
	i = 0;
	pos = -1;
	while (pos < 0 && g_sigenv.envp[i])
	{
		if (ft_strncmp(g_sigenv.envp[i], name, (ft_strlen(name) + 1)) == '=')
			pos = i;
		else
			i++;
	}
	if (!g_sigenv.envp[i])
		return (-1);
	return (pos);
}

char	*get_env(char *name)
{
	int				pos;

	if (!name)
		return (NULL);
	if (!ft_strncmp(name, "?", 2))
		return (g_sigenv.last_status);
	pos = get_pos_vble(name);
	if (pos < 0)
		return (NULL);
	return (ft_strchr(g_sigenv.envp[pos], '=') + 1);
}
