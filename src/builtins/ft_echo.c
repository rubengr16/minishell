/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:26:53 by rgallego          #+#    #+#             */
/*   Updated: 2023/09/07 18:13:22 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	is_n_valid(char **args, int *new_line, int *i)
{
	int	j;

	*i = 1;
	while (args[*i])
	{
		if (!ft_strncmp(args[*i], "-", 2))
			return ;
		j = 0;
		if (args[*i][j++] != '-')
			return ;
		while (args[*i][j] && args[*i][j] == 'n')
		{
			*new_line = 1;
			j++;
		}
		if (args[*i][j])
		{
			if (*i == 1)
				*new_line = 0;
			return ;
		}
		(*i)++;
	}
}

void	ft_echo(char **args)
{
	int	new_line;
	int	i;

	new_line = 0;
	if (2 <= len_char_double_ptr(args))
	{
		is_n_valid(args, &new_line, &i);
		while (args[i])
		{
			printf("%s", args[i]);
			i++;
			if (args[i])
				printf(" ");
		}
	}
	if (!new_line)
		printf("\n");
	g_sigenv.our_errno = 0;
}
