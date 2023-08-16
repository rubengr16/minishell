/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:35:16 by rgallego          #+#    #+#             */
/*   Updated: 2023/08/16 15:50:41 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	set_vble(char *vble, char *equal_sign)
{
	char	*vble_cpy;
	int		pos;

	vble_cpy = ft_strdup(vble);
	if (!vble_cpy)
		return ((void)mini_error(NULL, NULL, SYS_ERR, NULL));
	*equal_sign = '\0';
	pos = get_pos_vble(vble);
	if (0 <= pos)
	{
		free(g_sigenv.envp[pos]);
		g_sigenv.envp[pos] = vble_cpy;
	}
	(void)add_to_char_double_ptr(&g_sigenv.envp, vble_cpy);
}

static int	is_valid_vble_name(char *s)
{
	int	i;

	i = 0;
	if (!s || !*s)
		return (0);
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
		i++;
	if ((!i && s[i] == '=') || (s[i] && s[i] != '='))
		return (0);
	return (1);
}

static void	export_error(char *identifier)
{
	ft_putstr_fd("minishell: export: ", STDERR_FILENO);
	if (identifier && *identifier)
	{
		ft_putstr_fd(identifier, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(NOT_VALID_IDENTIFIER_MSG, STDERR_FILENO);
	}
	else
		ft_putendl_fd(NOT_IN_CONTEXT_MSG, STDERR_FILENO);
	errno = 1;
}

void	ft_export(char **args)
{
	char	*equal_sign;
	int		i;

	if (len_char_double_ptr(args) <= 1)
		return ;
	i = 1;
	errno = 0;
	while (0 < i && args[i])
	{
		if (!is_valid_vble_name(args[i]))
			export_error(args[i]);
		else
		{
			equal_sign = ft_strchr(args[i], '=');
			if (equal_sign)
				set_vble(args[i], equal_sign);
		}
		i++;
	}
}
