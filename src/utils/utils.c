/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 17:57:50 by rgallego          #+#    #+#             */
/*   Updated: 2023/09/07 18:16:31 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*mini_error(char *s1, char *s2, int errcode, void *to_free)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(s1, STDERR_FILENO);
	if (s1 && (s2 || errcode < 0))
		ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(s2, STDERR_FILENO);
	if (s2 && errcode < 0)
		ft_putstr_fd(": ", STDERR_FILENO);
	if (0 < errcode)
		g_sigenv.our_errno = errcode;
	else
	{
		g_sigenv.our_errno = errno;
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
	}
	ft_putchar_fd('\n', STDERR_FILENO);
	if (to_free)
		free(to_free);
	return (NULL);
}

char	**add_to_char_double_ptr(char ***char_double_ptr, char *str)
{
	unsigned int	i;
	char			**aux;

	i = 0;
	if (*char_double_ptr)
		while ((*char_double_ptr)[i])
			i++;
	aux = malloc(sizeof(char *) * (i + 2));
	if (!aux)
		return (mini_error(NULL, NULL, SYS_ERR, str));
	i = 0;
	if (*char_double_ptr)
	{
		while ((*char_double_ptr)[i])
		{
			aux[i] = (*char_double_ptr)[i];
			i++;
		}
	}
	aux[i] = str;
	aux[i + 1] = NULL;
	free(*char_double_ptr);
	*char_double_ptr = aux;
	return (*char_double_ptr);
}

unsigned int	len_char_double_ptr(char **char_double_ptr)
{
	unsigned int	i;

	if (!char_double_ptr)
		return (0);
	i = 0;
	while (char_double_ptr[i])
		i++;
	return (i);
}

char	**free_double_char_ptr(char **char_double_ptr)
{
	unsigned int	i;

	if (!char_double_ptr)
		return (NULL);
	i = 0;
	while (char_double_ptr[i])
	{
		free(char_double_ptr[i]);
		i++;
	}
	free(char_double_ptr);
	char_double_ptr = NULL;
	return (char_double_ptr);
}

int	isstrspace(char *s)
{
	int	i;

	i = 0;
	if (s)
		while (s[i] && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'
				|| s[i] == '\v' || s[i] == '\f' || s[i] == '\r'))
			i++;
	return (!s || !s[i]);
}
