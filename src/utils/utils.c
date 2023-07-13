/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 17:57:50 by rgallego          #+#    #+#             */
/*   Updated: 2023/07/14 00:24:37 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*mini_error(char *optional_str, char *str, void *to_free)
{
	if (to_free)
		free(to_free);
	to_free = NULL;
	ft_putstr_fd("minishell: ", STDOUT_FILENO);
	ft_putstr_fd(optional_str, STDOUT_FILENO);
	ft_putendl_fd(str, STDOUT_FILENO);
	return (NULL);
}

void	free_double_char_ptr(char **char_double_ptr)
{
	unsigned int	i;

	i = 0;
	while (char_double_ptr[i])
	{
		free(char_double_ptr[i]);
		i++;
	}
	free(char_double_ptr);
}
