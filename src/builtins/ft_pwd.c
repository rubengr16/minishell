/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:34:37 by rgallego          #+#    #+#             */
/*   Updated: 2023/07/23 20:38:23 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "builtins.h"

void	ft_pwd(void)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	printf("%s\n", dir);
	free(dir);
}
