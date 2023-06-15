/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 19:10:35 by rgallego          #+#    #+#             */
/*   Updated: 2023/06/16 01:12:03 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include "libft.h"

/* ******************************* ENUM ******************************* */
enum	e_state
{
	NORMAL,
	SINGLE_QUOTES = '\'',
	DOUBLE_QUOTES = '\"',
	METACHARACTER
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

t_token			*new_token(char *str, unsigned int size, enum e_state context);
void			print_list(t_token_list *list);
t_token_list	*tokenize(char *line);
void			delete_list(t_token_list *list);
int				add_to_list(t_token_list *list, t_token *token);
t_token_list	*create_list(void);

#endif
