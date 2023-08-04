/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 17:55:34 by rgallego          #+#    #+#             */
/*   Updated: 2023/08/05 01:13:52 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <string.h>
# include <errno.h>
# include "libft.h"
# include "get_next_line.h"

# define AMBIGUOUS_REDIR_MSG "ambiguous redirect"
# define NO_HOME_MSG "HOME not set"
# define UNEXPECTED_TK_MSG "syntax error near unexpected token: "
# define UNCLOSED_Q_MSG "unclosed quotes found"

# define SYS_ERR -1
# define AMBIG_ERR 1
# define NO_HOME_ERR 1
# define SYNTAX_ERR 2

/* ***************************** FUNC DECLARATION ************************** */
/* ---------------------------------- UTILS -------------------------------- */
void			*mini_error(char *s1, char *s2, int errcode, void *to_free);
char			**add_to_char_double_ptr(char ***char_double_ptr, char *str);
unsigned int	len_char_double_ptr(char **char_double_ptr);
void			free_double_char_ptr(char **char_double_ptr);

#endif
