/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:35:44 by rgallego          #+#    #+#             */
/*   Updated: 2023/07/23 20:38:24 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_unset(char ***my_envp, char **args)
{
	char			**aux;
	unsigned int	i;
	unsigned int	j;

	if (!*my_envp && len_char_double_ptr(args) <= 1)
		return ;
	i = 1;
	aux = *my_envp;
	while (aux && args[i])
	{
		j = 0;
		while ((*my_envp)[j] 
			&& (ft_strncmp((*my_envp)[j], args[i], ft_strlen(args[i])) == '='))
			j++;
		if ((*my_envp)[j])
		{

		}
		i++;
	}
}
