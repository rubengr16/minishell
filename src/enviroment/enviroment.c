/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:11:30 by rgallego          #+#    #+#             */
/*   Updated: 2023/08/14 12:41:11 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enviroment.h"

static char	*increment_shlvl(char *s)
{
	char	*aux;
	int		num_shlvl;

	if (!ft_strchr(s, '='))
		return (ft_strdup(s));
	s = ft_strchr(s, '=') + 1;
	num_shlvl = ft_atoi(s);
	if ((!num_shlvl || num_shlvl == -1) && (ft_strlen(s) > 2))
		return (ft_strdup(s));
	aux = ft_itoa(num_shlvl + 1);
	if (!aux)
		return (ft_strdup(s));
	s = ft_strjoin("SHLVL=", aux);
	free(aux);
	if (!s)
		return (ft_strdup(s));
	return (s);
}

char	**create_my_env(char **envp)
{
	unsigned int	i;

	i = 0;
	if (envp)
		while (envp[i])
			i++;
	g_sigenv.envp = malloc(sizeof(char *) * (i + 1));
	if (!g_sigenv.envp)
		mini_error(NULL, NULL, SYS_ERR, NULL);
	i = 0;
	while (g_sigenv.envp && envp[i])
	{
		if (!ft_strncmp(envp[i], "SHLVL=", 6))
			g_sigenv.envp[i] = increment_shlvl(envp[i]);
		else
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
	int				pos;

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
	if (!ft_strncmp(name, "?", 1))
		return (ft_itoa(errno));
	pos = get_pos_vble(name);
	if (pos < 0)
		return (NULL);
	return (ft_strchr(g_sigenv.envp[pos], '=') + 1);
}
