/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:11:30 by rgallego          #+#    #+#             */
/*   Updated: 2023/09/04 00:09:45 by rgallego         ###   ########.fr       */
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

static char	**always_shlvl(void)
{
	char	*shlvl;

	shlvl = ft_strdup("SHLVL=1");
	if (!shlvl)
		return (mini_error(NULL, NULL, SYS_ERR, NULL));
	g_sigenv.envp = malloc(sizeof(char *) * 2);
	if (!g_sigenv.envp)
		return (mini_error(NULL, NULL, SYS_ERR, NULL));
	g_sigenv.envp[0] = shlvl;
	g_sigenv.envp[1] = NULL;
	return (g_sigenv.envp);
}

char	**create_my_env(char **envp)
{
	unsigned int	i;

	if (envp && !envp[0])
		return (always_shlvl());
	i = 0;
	if (envp)
		while (envp[i])
			i++;
	g_sigenv.envp = malloc(sizeof(char *) * (i + 1));
	if (!g_sigenv.envp)
		return (mini_error(NULL, NULL, SYS_ERR, NULL));
	i = 0;
	while (envp && envp[i])
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
