/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 19:10:35 by rgallego          #+#    #+#             */
/*   Updated: 2023/06/21 22:44:03 by rgallego         ###   ########.fr       */
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
	struct s_token	*next;
}	t_token;

typedef struct s_token_list
{
	t_token	*start;
	t_token	*end;
}	t_token_list;

typedef struct s_env_vbles
{
	char			*value;
	unsigned int	len;
}	t_env_vbles;

/* ***************************** FUNC DECLARATION ************************** */
t_token			*new_token(char *str, unsigned int size);
void			print_list(t_token_list *list);
t_token_list	*tokenize(char **line);
void			delete_list(t_token_list *list);
int				add_to_list(t_token_list *list, t_token *token);
t_token_list	*create_list(void);
unsigned int	get_state(char c);
int				expand(char **line, unsigned int *i, enum e_state state);

#endif
