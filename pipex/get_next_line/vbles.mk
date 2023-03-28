SRC_DIR = 			src/

INC_DIR =			inc/

SRCS	=			\
					$(addprefix $(SRC_DIR), \
					get_next_line.c \
					get_next_line_utils.c \
					)

SRCSBONUS	=		\
					$(addprefix $(SRC_DIR), \
					get_next_line_bonus.c \
					get_next_line_utils_bonus.c \
					)

OBJS	=			$(SRCS:.c=.o)

OBJSBONUS	=		$(SRCSBONUS:.c=.o)

DPNDS	=			$(SRCS:.c=.d)

DPNDSBONUS	=		$(SRCSBONUS:.c=.d)

CC		=			gcc

RM		=			-rm -f

AR		=			ar rcs

CFLAGS	=			-Wall -Werror -Wextra -D BUFFER_SIZE=42 -MD

NAME	=			get_next_line.a
