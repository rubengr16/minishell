/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 19:54:48 by rgallego          #+#    #+#             */
/*   Updated: 2023/06/24 20:06:19 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include "libft.h"
# include "parser.h"

/* ******************************* ENUM ******************************* */
enum	e_state
{
	NORMAL,
	SPACE_CHAR = ' ',
	SINGLE_QUOTE = '\'',
	DOUBLE_QUOTE = '\"',
	METACHAR
};

/* ******************************* TOKEN LIST ******************************* */
typedef struct s_token
{
	char			*token;
	enum e_state	context;
	struct s_token	*next;
}	t_token;

typedef struct s_token_list
{
	t_token	*start;
	t_token	*end;
}	t_token_list;

/* ***************************** FUNC DECLARATION ************************** */
/* ---------------------------------- UTILS -------------------------------- */

/* -------------------------------- TOKEN_LST ------------------------------ */

/* --------------------------------- EXPAND -------------------------------- */

/* -------------------------------- TOKENIZE ------------------------------- */


#endif
