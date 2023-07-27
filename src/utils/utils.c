/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 17:57:50 by rgallego          #+#    #+#             */
/*   Updated: 2023/07/27 18:50:55 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*mini_error(char *opt_str1, char *opt_str2, char *str, void *to_free)
{
	if (to_free)
		free(to_free);
	to_free = NULL;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(opt_str1, STDERR_FILENO);
	if (opt_str1)
		ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(opt_str2, STDERR_FILENO);
	if (opt_str2)
		ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
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
		return (mini_error(NULL, NULL, ALLOC_ERR, str));
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

void	free_double_char_ptr(char **char_double_ptr)
{
	unsigned int	i;

	i = 1;
	while (char_double_ptr[i])
	{
		free(char_double_ptr[i]);
		i++;
	}
	free(char_double_ptr);
}
