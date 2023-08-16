/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:26:53 by rgallego          #+#    #+#             */
/*   Updated: 2023/08/16 12:37:18 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	is_n_valid(char **args, int *new_line, int *i)
{
	int	j;

	*i = 0;
	j = -1;
	while (args[*i] && (j < 0 || !args[*i][j]))
	{
		(*i)++;
		j = 0;
		while (args[*i] && args[*i][j]
			&& ((!j && args[*i][j] == '-') || (0 < j && args[*i][j] == 'n')))
			j++;
		if (args[*i] && !args[*i][j])
			*new_line = 1;
	}
	return (args[*i][j]);
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
	errno = 0;
}
