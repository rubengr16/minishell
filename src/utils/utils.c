/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: socana-b <socana-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 17:57:50 by rgallego          #+#    #+#             */
/*   Updated: 2023/07/18 20:18:46 by socana-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*mini_error(char *optional_str, char *str)
{
	ft_putstr_fd("minishell: ", STDOUT_FILENO);
	ft_putstr_fd(optional_str, STDOUT_FILENO);
	ft_putendl_fd(str, STDOUT_FILENO);
	return (NULL);
}

void	free_double_char_ptr(char **char_double_ptr)
{
	unsigned int	i;

	i = 1;
	while (char_double_ptr[i])
	{
		free(char_double_ptr[i]);
		i++;
	}
	free(char_double_ptr);
}
