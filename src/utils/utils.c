/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 17:57:50 by rgallego          #+#    #+#             */
/*   Updated: 2023/06/26 22:01:36 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*mini_error(char *str)
{
	ft_putstr_fd("minishell: ", STDOUT_FILENO);
	ft_putendl_fd(str, STDOUT_FILENO);
	return (NULL);
}
