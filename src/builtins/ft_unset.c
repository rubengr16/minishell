/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:35:44 by rgallego          #+#    #+#             */
/*   Updated: 2023/08/14 11:35:14 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	ft_unset_vble(char ***aux, int pos)
{
	int	i;

	i = 0;
	while (0 <= pos && g_sigenv.envp[i])
	{
		if (pos == i)
			free(g_sigenv.envp[pos]);
		else if (!add_to_char_double_ptr(aux, g_sigenv.envp[i]))
			pos = -1;
		i++;
	}
	return (pos);
}

void	ft_unset(char **args)
{
	char			**aux;
	unsigned int	i;
	int				pos;

	if (!g_sigenv.envp || len_char_double_ptr(args) <= 1)
		return ;
	i = 1;
	pos = 0;
	aux = NULL;
	while (0 <= pos && args[i])
	{
		pos = get_pos_vble(args[i]);
		if (0 <= pos)
			pos = ft_unset_vble(&aux, pos);
		else
			pos = 0;
		i++;
	}
	i = 0;
	free(g_sigenv.envp);
	g_sigenv.envp = aux;
	if (pos < 0)
		g_sigenv.my_errno = 1;
	else
		g_sigenv.my_errno = 0;
}
