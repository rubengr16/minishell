/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 10:05:45 by rgallego          #+#    #+#             */
/*   Updated: 2022/02/21 14:36:48 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strchr_nl(char *str, int *pos_nl)
{
	*pos_nl = 0;
	if (str)
	{
		while (str[*pos_nl] && str[*pos_nl] != '\n')
			(*pos_nl)++;
		if (str[*pos_nl] == '\n')
			return (1);
	}
	return (0);
}

void	ft_strcpy(char *dest, char *src, int len)
{
	int	cnt;

	cnt = 0;
	if (src)
	{
		while (cnt < len && src[cnt])
		{
			dest[cnt] = src[cnt];
			cnt++;
		}
	}
}

int	strjoin_gnl(char **dest, char *src, int len1, int len2)
{
	char	*aux;

	aux = *dest;
	if (src[len2] == '\n')
		len2++;
	*dest = malloc(sizeof(char) * (len1 + len2 + 1));
	if (*dest)
	{
		ft_strcpy(*dest, aux, len1);
		ft_strcpy((*dest) + len1, src, len2);
		(*dest)[len1 + len2] = '\0';
		free(aux);
		return (len1 + len2);
	}
	else
		return (-1);
}

void	ft_free_resources(char **str)
{
	free(*str);
	*str = NULL;
}

void	read_line(char **line, char **rest, int len, int fd)
{
	char	*buffer;
	int		n_char;
	int		pos_nl;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer)
	{
		n_char = BUFFER_SIZE;
		pos_nl = BUFFER_SIZE;
		while (n_char == BUFFER_SIZE && pos_nl == BUFFER_SIZE && len >= 0)
		{
			n_char = read(fd, buffer, BUFFER_SIZE);
			if (n_char > 0)
			{
				buffer[n_char] = '\0';
				(void)ft_strchr_nl(buffer, &pos_nl);
				len = strjoin_gnl(line, buffer, len, pos_nl);
			}
		}
		if (n_char > 0 && (pos_nl + 1) < n_char && len >= 0)
			strjoin_gnl(rest, &buffer[pos_nl + 1], 0, n_char - pos_nl - 1);
	}
	if (!buffer || len == -1 || n_char == -1)
		ft_free_resources(line);
	free(buffer);
}
