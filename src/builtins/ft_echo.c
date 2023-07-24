/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:26:53 by rgallego          #+#    #+#             */
/*   Updated: 2023/07/24 12:55:21 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_echo(char **args)
{
	int	new_line;
	int	i;

	new_line = 0;
	if (2 <= len_char_double_ptr(args) && !ft_strncmp(args[1], "-n\0", 3))
		new_line = 1;
	i = new_line + 1;
	while (args[i])
	{
		printf("%s", args[i]);
		i++;
		if (args[i])
			printf(" ");
	}
	if (!new_line)
		printf("\n");
}
