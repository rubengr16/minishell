/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 19:10:35 by rgallego          #+#    #+#             */
/*   Updated: 2023/06/26 21:45:33 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include "utils.h"

# define ALLOC_ERR "allocation failed"
# define UNCLOSED_Q_ERR "unclosed quotes found"

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
unsigned int	get_state(char c);
int				is_end_of_token(char c, enum e_state state);
int				is_end_of_vble(char c, enum e_state state);
int				is_true_quote(char c, enum e_state state);
int				is_true_char(char c, enum e_state state);

/* -------------------------------- TOKEN_LST ------------------------------ */
t_token			*new_token(char *str, unsigned int size, enum e_state state);
void			print_list(t_token_list *list); // DELETE WHEN FINISHED
void			delete_list(t_token_list *list);
t_token			*add_to_list(t_token_list *list, t_token *token);
t_token_list	*create_list(void);
/* --------------------------------- EXPAND -------------------------------- */
char			*expand(char **line, unsigned int *i, enum e_state state);
/* -------------------------------- TOKENIZE ------------------------------- */
t_token_list	*tokenize(char **line);

#endif
