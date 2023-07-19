/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 19:54:48 by rgallego          #+#    #+#             */
/*   Updated: 2023/07/19 10:41:35 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include "libft.h"
# include "parser.h"
# include "utils.h"

# define TRANS_VBLE_SPACE -4

# define UNEXPECTED_TK "syntax error near unexpected token: "
# define AMBIGUOUS_REDIR "ambiguous redirect"
# define SPLIT_ERR "split failed"

/* ******************************* ENUM ******************************* */
enum	e_token_type
{
	OTHER,
	PIPE,
	R_IN,
	R_IN_HERE_DOC,
	R_OUT,
	R_OUT_APPEND,
};

/* ***************************** COMMAND LIST ****************************** */
typedef struct s_redir
{
	char				*file;
	enum e_token_type	type;
	struct s_redir		*next;
}	t_redir;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	t_redir			*r_in;
	t_redir			*r_out;
	struct s_cmd	*next;
}	t_cmd;

/* ***************************** FUNC DECLARATION ************************** */
/* --------------------------------- UTILS --------------------------------- */
char				**add_to_char_double_ptr(char ***char_double_ptr,
						char *str);
enum e_token_type	get_token_type(char *token);
void				ft_strrepl(char *str, char old_char, char new_char);
/* --------------------------------- REDIR --------------------------------- */
t_redir				*insert_to_redir_list(t_redir **list, char *file,
						enum e_token_type type);
void				delete_redir_list(t_redir **list);
/* ---------------------------------- CMD ---------------------------------- */
t_cmd				*new_cmd(void);
t_cmd				*add_to_cmd_list(t_cmd **list);
void				delete_cmd_list(t_cmd **list);
void				print_cmd_list(t_cmd *list);
/* --------------------------------- EXPAND -------------------------------- */
char				*expand(char **line, unsigned int *i, enum e_state state,
						unsigned int is_redir);
/* ------------------------------- REAL_TOKEN ------------------------------ */
char				*get_real_token(char *token, unsigned int is_redir);
/* --------------------------------- LEXER --------------------------------- */
t_cmd				*lexer(t_token_list **token_list);
#endif
