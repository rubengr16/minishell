/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 19:10:35 by rgallego          #+#    #+#             */
/*   Updated: 2023/06/23 01:38:54 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>	// getenv()
# include "minishell.h"
# include "libft.h"

/* ******************************* ENUM ******************************* */
enum	e_state
{
	NORMAL,
	SPACE_CHAR = ' ',
	SINGLE_QUOTES = '\'',
	DOUBLE_QUOTES = '\"',
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
void			manage_quotes(enum e_state *state, unsigned int *i,
	unsigned int *adjust_size, char c);
/* -------------------------------- TOKEN_LST ------------------------------ */
t_token			*new_token(char *str, unsigned int size, enum e_state state);
void			print_list(t_token_list *list);
void			delete_list(t_token_list *list);
int				add_to_list(t_token_list *list, t_token *token);
t_token_list	*create_list(void);
/* --------------------------------- EXPAND -------------------------------- */
int				expand(char **line, unsigned int *i, enum e_state state);
/* -------------------------------- TOKENIZE ------------------------------- */
t_token_list	*tokenize(char **line);

#endif
