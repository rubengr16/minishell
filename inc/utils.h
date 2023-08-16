/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 17:55:34 by rgallego          #+#    #+#             */
/*   Updated: 2023/08/16 13:31:18 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <string.h>
# include <errno.h>
# include <stdio.h>
# include "libft.h"
# include "global.h"

# define AMBIG_REDIR_MSG "ambiguous redirect"
# define NO_HOME_MSG "HOME not set"
# define NUMERIC_ARGS_MSG "numeric argument required"
# define NOT_VALID_IDENTIFIER_MSG "not a valid identifier"
# define TOO_MANY_ARGS_MSG "too many arguments"
# define UNEXPECTED_TK_MSG "syntax error near unexpected token"
# define UNCLOSED_Q_MSG "unclosed quotes found"
# define EXEC_DENIED_MSG "permission denied"
# define CMD_NOT_FOUND_MSG "command not found..."

# define SYS_ERR -1
# define AMBIG_ERR 1
# define NO_HOME_ERR 1
# define NUMERIC_ARGS_ERR 2
# define TOO_MANY_ARGS_ERR 1
# define UNEXPECTED_TK_ERR 2
# define SYNTAX_ERR 2
# define EXEC_DENIED_ERR 126
# define CMD_NOT_FOUND_ERR 127
# define EXPORT_ERR -2

/* ***************************** FUNC DECLARATION ************************** */
/* ---------------------------------- UTILS -------------------------------- */
void			*mini_error(char *s1, char *s2, int errcode, void *to_free);
char			**add_to_char_double_ptr(char ***char_double_ptr, char *str);
unsigned int	len_char_double_ptr(char **char_double_ptr);
char			**free_double_char_ptr(char **char_double_ptr);
int				isstrspace(char *s);

#endif
