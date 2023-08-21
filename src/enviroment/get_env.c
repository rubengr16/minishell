/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:40:06 by rgallego          #+#    #+#             */
/*   Updated: 2023/08/21 18:40:56 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enviroment.h"

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
