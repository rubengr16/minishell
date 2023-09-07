/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:35:16 by rgallego          #+#    #+#             */
/*   Updated: 2023/09/07 18:14:03 by rgallego         ###   ########.fr       */
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
	else
		(void)add_to_char_double_ptr(&g_sigenv.envp, vble_cpy);
}

int	is_valid_vble_name(char *s, unsigned int is_export)
{
	int	i;

	i = 0;
	if (!s || !*s || ft_isdigit(*s))
		return (0);
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
		i++;
	if ((is_export && ((!i && s[i] == '=') || (s[i] && s[i] != '=')))
		|| (!is_export && s[i]))
		return (0);
	return (1);
}

void	export_unset_error(char *cmd, char *identifier)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (identifier && *identifier)
	{
		ft_putstr_fd(identifier, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(NOT_VALID_IDENTIFIER_MSG, STDERR_FILENO);
	}
	else
		ft_putendl_fd(NOT_IN_CONTEXT_MSG, STDERR_FILENO);
	g_sigenv.our_errno = 1;
}

void	ft_export(char **args)
{
	char	*equal_sign;
	int		i;

	if (len_char_double_ptr(args) <= 1)
		return ;
	i = 1;
	g_sigenv.our_errno = 0;
	while (0 < i && args[i])
	{
		if (!is_valid_vble_name(args[i], 1))
			export_unset_error("export", args[i]);
		else
		{
			equal_sign = ft_strchr(args[i], '=');
			if (equal_sign)
				set_vble(args[i], equal_sign);
		}
		i++;
	}
}
