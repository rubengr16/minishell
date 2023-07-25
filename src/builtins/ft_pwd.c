/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:34:37 by rgallego          #+#    #+#             */
/*   Updated: 2023/07/25 09:02:52 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "builtins.h"

void	ft_pwd(void)
{
	printf("%s\n", get_env("PWD"));
	exit(0);
}
