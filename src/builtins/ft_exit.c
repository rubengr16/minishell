/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 18:22:20 by rgallego          #+#    #+#             */
/*   Updated: 2023/09/07 18:13:58 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	ft_isstrnbr(char *s)
{
	unsigned int	i;

	if (!s)
		return (0);
	i = 0;
	if (s[i] == '-')
	{
		i++;
		if (!ft_isdigit(s[i]))
			return (0);
	}
	while (s[i] && ft_isdigit(s[i]))
		i++;
	if (s[i])
		return (0);
	return (1);
}

void	ft_exit(char **args, int is_child)
{
	if (!is_child)
		printf("exit\n");
	if (1 < len_char_double_ptr(args) && !ft_isstrnbr(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[ARG_1], STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(NUMERIC_ARGS_MSG, STDERR_FILENO);
		g_sigenv.our_errno = NUMERIC_ARGS_ERR;
	}
	else if (2 < len_char_double_ptr(args))
		return ((void)mini_error(args[CMD], TOO_MANY_ARGS_MSG,
				TOO_MANY_ARGS_ERR, NULL));
	else if (2 == len_char_double_ptr(args))
		g_sigenv.our_errno = ft_atoi(args[ARG_1]) % 256;
	else
		g_sigenv.our_errno = 0;
	exit(g_sigenv.our_errno);
}
