/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:35:16 by rgallego          #+#    #+#             */
/*   Updated: 2023/07/24 12:28:34 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	set_vble(char *vble, char *equal_sign)
{
	char	*vble_cpy;
	int		pos;

	vble_cpy = ft_strdup(vble);
	if (!vble_cpy)
	{
		(void)mini_error(NULL, NULL, ALLOC_ERR, NULL);
		return (EXPORT_ERR);
	}
	*equal_sign = '\0';
	pos = get_pos_vble(vble);
	if (0 <= pos)
	{
		free(g_sigenv.envp[pos]);
		g_sigenv.envp[pos] = vble_cpy;
	}
	else if (!add_to_char_double_ptr(&g_sigenv.envp, vble_cpy))
		return (EXPORT_ERR);
	return (0);
}

void	ft_export(char **args)
{
	char	*equal_sign;
	int		i;

	if (len_char_double_ptr(args) <= 1)
		return ;
	i = 1;
	while (0 < i && args[i])
	{
		equal_sign = ft_strchr(args[i], '=');
		if (equal_sign && set_vble(args[i], equal_sign))
			i = EXPORT_ERR;
		i++;
	}
}
