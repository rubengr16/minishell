/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 19:54:48 by rgallego          #+#    #+#             */
/*   Updated: 2023/06/26 21:53:02 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include "libft.h"
# include "parser.h"

/* ******************************* ENUM ******************************* */
enum	e_redir_type
{
	R_IN,
	R_IN_HERE_DOC,
	R_OUT,
	R_OUT_APPEND,
};

/* ***************************** COMMAND LIST ****************************** */
typedef struct s_redir
{
	char				*file;
	enum e_redir_type	*type;
	struct s_redir		*next;
}	t_redir;

typedef struct s_cmd
{
	char			*cmd;
	char			*args;
	t_redir			*r_in;
	t_redir			*r_out;
	struct s_cmd	*next;
}	t_cmd;

/* ***************************** FUNC DECLARATION ************************** */
/* ---------------------------------- UTILS -------------------------------- */

/* -------------------------------- TOKEN_LST ------------------------------ */

/* --------------------------------- EXPAND -------------------------------- */

/* -------------------------------- TOKENIZE ------------------------------- */


#endif
