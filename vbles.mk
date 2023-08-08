# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    vbles.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/28 19:42:48 by rgallego          #+#    #+#              #
#    Updated: 2023/08/02 18:29:19 by rgallego         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR		=		src/

PARSER_DIR	=		parser/

LEXER_DIR	=		lexer/

ENV_DIR		=		enviroment/

BUILTINS_DIR	=	builtins/

EXEC_DIR	=		executor/

UTILS_DIR	=		utils/

SIGNALS_DIR	=		signals/

INC_DIR		=		inc/

MINISHELL	=		main.c

PARSER		=		$(addprefix $(PARSER_DIR), \
					utils.c \
					token_lst.c \
					tokenize.c \
					)

LEXER		=		$(addprefix $(LEXER_DIR), \
					utils.c \
					redir.c \
					cmd.c \
					expand.c \
					real_token.c \
					lexer.c \
					)

EXECUTOR		=	$(addprefix $(EXEC_DIR), \
					execute.c \
					utils.c \
					redirect.c \
					)

ENVIROMENT	=		$(addprefix $(ENV_DIR), \
					enviroment.c \
					)

BUILTINS	=	$(addprefix $(BUILTINS_DIR), \
					ft_cd.c \
					ft_echo.c \
					ft_env.c \
					ft_export.c \
					ft_pwd.c \
					ft_unset.c \
					)

UTILS		=		$(addprefix $(UTILS_DIR), \
					utils.c \
					)

SIGNALS		=		$(addprefix $(SIGNALS_DIR), \
					signals.c \
					)

SRCS		= 		$(addprefix $(SRC_DIR), \
					$(MINISHELL) \
					$(PARSER) \
					$(LEXER) \
					$(ENVIROMENT) \
					$(BUILTINS) \
					$(EXECUTOR) \
					$(UTILS) \
					$(SIGNALS) \
					)

OBJS	=			$(SRCS:.c=.o)

DPNDS	=			$(SRCS:.c=.d)

CC		=			gcc

RM		=			-rm -f

CFLAGS	=			-Wall -Werror -Wextra -MD

LDFLAGS	=			$(LIBFTNAME) \
					$(GNLNAME)

NAME	=			minishell

INC_ALL	=			\
					$(INC_DIR) \
					$(LIBFT)$(INC_DIR) \
					$(GNL)$(INC_DIR)

LIB_ALL = 			\
					readline

LIBFT	=			libft/

LIBFTNAME	=		$(LIBFT)libft.a

GNL		=			get_next_line/

GNLNAME	=			$(GNL)get_next_line.a
