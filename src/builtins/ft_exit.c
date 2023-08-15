/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 18:22:20 by rgallego          #+#    #+#             */
/*   Updated: 2023/08/15 20:03:50 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	ft_isstrnbr(char *s)
{
	unsigned int	i;

	if (!s)
		return (0);
	i = 0;
	if (s[i] == '-' && !ft_isdigit(s[i + 1]))
		return (0);
	i++;
	while (s[i] && ft_isdigit(s[i]))
		i++;
	if (s[i])
		return (0);
	return (1);
}

void	ft_exit(char **args)
{
	printf("exit\n");
	if (1 < len_char_double_ptr(args) && !ft_isstrnbr(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[ARG_1], STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
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
