/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 18:22:20 by rgallego          #+#    #+#             */
/*   Updated: 2023/08/14 01:52:58 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_exit(char **args)
{
	printf("exit\n");
	if (1 < len_char_double_ptr(args) && !ft_isstrnbr(args[1]))
	{
		mini_error(NULL, args[CMD], NUMERIC_ARGS_ERR, NULL);
		mini_error(args[ARG_1], NUMERIC_ARGS_MSG, NUMERIC_ARGS_ERR, NULL);
	}
	else if (2 < len_char_double_ptr(args))
		mini_error(args[CMD], TOO_MANY_ARGS_MSG, TOO_MANY_ARGS_ERR, NULL);
	else if (2 == len_char_double_ptr(args))
		errno = ft_atoi(args[ARG_1]) % 256;
	else
		errno = 0;
	exit(errno);
}
