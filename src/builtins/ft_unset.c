/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:35:44 by rgallego          #+#    #+#             */
/*   Updated: 2023/07/24 00:16:02 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	ft_unset_vble(char **my_envp, char ***aux, int pos)
{
	int	i;

	i = 0;
	while (0 <= pos && my_envp[i])
	{
		if (pos == i)
			free(my_envp[pos]);
		else if (!add_to_char_double_ptr(aux, my_envp[i]))
			pos = -1;
		i++;
	}
	return (pos);
}

void	ft_unset(char ***my_envp, char **args)
{
	char			**aux;
	unsigned int	i;
	int				pos;

	if (!*my_envp || len_char_double_ptr(args) <= 1)
		return ;
	i = 1;
	pos = 0;
	aux = NULL;
	while (0 <= pos && args[i])
	{
		pos = get_pos_vble(*my_envp, args[i]);
		if (0 <= pos)
			pos = ft_unset_vble(*my_envp, &aux, pos);
		else
			pos = 0;
		i++;
	}
	i = 0;
	free(*my_envp);
	*my_envp = aux;
}
