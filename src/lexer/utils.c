/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 23:43:22 by rgallego          #+#    #+#             */
/*   Updated: 2023/09/04 18:46:10 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

enum e_token_type	get_token_type(char *token)
{
	size_t	len;

	len = ft_strlen(token);
	if (!ft_strncmp("|", token, len))
		return (PIPE);
	if (!ft_strncmp("<", token, len))
		return (R_IN);
	if (!ft_strncmp("<<", token, len))
		return (R_IN_HERE_DOC);
	if (!ft_strncmp(">", token, len))
		return (R_OUT);
	if (!ft_strncmp(">>", token, len))
		return (R_OUT_APPEND);
	return (OTHER);
}

void	empty_token_split(char ***splitted_token)
{
	char	*str;

	str = ft_strdup("");
	if (!str)
	{
		(void)mini_error(NULL, NULL, SYS_ERR, NULL);
		free_double_char_ptr(*splitted_token);
		return ;
	}
	*splitted_token = add_to_char_double_ptr(splitted_token, str);
}

void	ft_strreplset(char *str, char *set, char new_char)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		if (ft_strchr(set, str[i]))
			str[i] = new_char;
		i++;
	}
}
