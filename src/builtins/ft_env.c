/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 09:40:49 by rgallego          #+#    #+#             */
/*   Updated: 2023/07/25 09:02:30 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_env(void)
{
	unsigned int	i;

	if (!g_sigenv.envp)
		return ;
	i = 0;
	while (g_sigenv.envp[i])
	{
		ft_putendl_fd(g_sigenv.envp[i], STDOUT_FILENO);
		i++;
	}
	exit(0);
}
