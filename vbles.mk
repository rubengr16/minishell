# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    vbles.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/28 19:42:48 by rgallego          #+#    #+#              #
#    Updated: 2023/06/26 23:44:08 by rgallego         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR		=		src/

PARSER_DIR	=		parser/

LEXER_DIR	=		lexer/

ENV_DIR		=		enviroment/

UTILS_DIR	=		utils/

INC_DIR		=		inc/

MINISHELL	=		main.c

PARSER		=		$(addprefix $(PARSER_DIR), \
					utils.c \
					token_lst.c \
					expand.c \
					tokenize.c \
					)

LEXER		=		$(addprefix $(LEXER_DIR), \
					utils.c \
					redir.c \
					cmd.c \
					lexer.c \
					)

ENVIROMENT	=		$(addprefix $(ENV_DIR), \
					enviroment.c \
					builtins.c	\
					env_utils.c	\
					)

UTILS		=		$(addprefix $(UTILS_DIR), \
					utils.c \
					)

SRCS		= 		$(addprefix $(SRC_DIR), \
					$(MINISHELL) \
					$(PARSER) \
					$(LEXER) \
					$(ENVIROMENT) \
					$(UTILS) \
					)

OBJS	=			$(SRCS:.c=.o)

DPNDS	=			$(SRCS:.c=.d)

CC		=			gcc

RM		=			-rm -f

CFLAGS	=			-Wall -Werror -Wextra -MD -fsanitize=address -g3

LDFLAGS	=			$(LIBFTNAME)

NAME	=			minishell

INC_ALL	=			\
					$(INC_DIR) \
					$(LIBFT)$(INC_DIR)

LIB_ALL = 			\
					readline

LIBFT	=			libft/

LIBFTNAME	=		$(LIBFT)libft.a
