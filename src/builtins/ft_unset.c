/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:35:44 by rgallego          #+#    #+#             */
/*   Updated: 2023/09/07 18:14:06 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	ft_unset_vble(char ***aux, char *name)
{
	int	pos;
	int	i;

	pos = get_pos_vble(name);
	if (pos < 0)
		return ;
	i = 0;
	while (0 <= pos && g_sigenv.envp[i])
	{
		if (pos == i)
			free(g_sigenv.envp[pos]);
		else if (!add_to_char_double_ptr(aux, g_sigenv.envp[i]))
			pos = -2;
		i++;
	}
	free(g_sigenv.envp);
	g_sigenv.envp = *aux;
	*aux = NULL;
}

void	ft_unset(char **args)
{
	char			**aux;
	unsigned int	i;

	if (!g_sigenv.envp || len_char_double_ptr(args) <= 1)
		return ;
	i = 1;
	aux = NULL;
	g_sigenv.our_errno = 0;
	while (args[i])
	{
		if (!is_valid_vble_name(args[i], 0))
			export_unset_error("unset", args[i]);
		else
			ft_unset_vble(&aux, args[i]);
		i++;
	}
}
