/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: socana-b <socana-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 09:40:49 by rgallego          #+#    #+#             */
/*   Updated: 2023/09/05 19:43:36 by socana-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_env(void)
{
	unsigned int	i;

	if (!g_sigenv.envp)
	{
		errno = 0;
		return ;
	}
	i = 0;
	while (g_sigenv.envp[i])
	{
		ft_putendl_fd(g_sigenv.envp[i], STDOUT_FILENO);
		i++;
	}
	errno = 0;
}
