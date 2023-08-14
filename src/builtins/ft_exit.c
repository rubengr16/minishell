/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 18:22:20 by rgallego          #+#    #+#             */
/*   Updated: 2023/08/14 10:28:00 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_exit(char **args)
{
	printf("exit\n");
	if (1 < len_char_double_ptr(args) && !ft_isstrnbr(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[ARG_1], STDERR_FILENO);
		ft_putendl_fd(NUMERIC_ARGS_MSG, STDERR_FILENO);
		errno = NUMERIC_ARGS_ERR;
	}
	else if (2 < len_char_double_ptr(args))
		mini_error(args[CMD], TOO_MANY_ARGS_MSG, TOO_MANY_ARGS_ERR, NULL);
	else if (2 == len_char_double_ptr(args))
		errno = ft_atoi(args[ARG_1]) % 256;
	else
		errno = 0;
	exit(errno);
}
