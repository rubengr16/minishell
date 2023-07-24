/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:35:16 by rgallego          #+#    #+#             */
/*   Updated: 2023/07/24 09:51:58 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_export(char **args)
{
	char	**aux;
	char	*vble_cpy;
	int		i;

	if (len_char_double_ptr(args) <= 1)
		return ;
	i = 1;
	aux = g_sigenv.envp;
	while (aux && args[i])
	{
		if (ft_strchr(args[i], '='))
		{
			vble_cpy = ft_strdup(args[i]);
			aux = add_to_char_double_ptr(&g_sigenv.envp, vble_cpy);
		}
		i++;
	}
}
