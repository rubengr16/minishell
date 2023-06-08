/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 19:10:35 by rgallego          #+#    #+#             */
/*   Updated: 2023/04/16 19:12:50 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/* ******************************* ENUM ******************************* */
enum
{
	NORMAL = 1,
	SINGLE_QUOTES = 2,
	DOUBLE_QUOTES = 3
};

/* ******************************* TOKEN LIST ******************************* */
typedef struct s_token
{
	char			*token;
	struct s_token	*next;
}t_token;

typedef struct s_list
{
	t_token *start;
	t_token *end;
}t_list;

/* ******************************* FUNC DECLARATION ******************************* */

t_token	*new_token(char *str, unsigned int length);
void	print_list(t_list *list);
t_list *tokenize(char *line);
void	delete_list(t_list *list);
int		add_to_list(t_list *list, t_token *token);
t_list	*create_list();