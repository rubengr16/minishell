SRC_DIR = 			src/

INC_DIR =			inc/

SRCS	=			\
					$(addprefix $(SRC_DIR), \
					ft_isalpha.c \
					ft_isdigit.c \
					ft_isalnum.c \
					ft_isascii.c \
					ft_isprint.c \
					ft_strlen.c \
					ft_memset.c \
					ft_bzero.c \
					ft_memcpy.c \
					ft_memmove.c \
					ft_strlcpy.c \
					ft_strlcat.c \
					ft_toupper.c \
					ft_tolower.c \
					ft_strchr.c \
					ft_strrchr.c \
					ft_strncmp.c \
					ft_memchr.c \
					ft_memcmp.c \
					ft_strnstr.c \
					ft_atoi.c \
					ft_calloc.c \
					ft_strdup.c \
					ft_substr.c \
					ft_strjoin.c \
					ft_strtrim.c \
					ft_split.c \
					ft_itoa.c \
					ft_strmapi.c \
					ft_striteri.c \
					ft_putchar_fd.c \
					ft_putstr_fd.c \
					ft_putendl_fd.c \
					ft_putnbr_fd.c \
					)

SRCSBONUS	=		\
					$(addprefix $(SRC_DIR), \
					ft_lstnew_bonus.c \
					ft_lstadd_front_bonus.c \
					ft_lstsize_bonus.c \
					ft_lstlast_bonus.c \
					ft_lstadd_back_bonus.c \
					ft_lstdelone_bonus.c \
					ft_lstclear_bonus.c \
					ft_lstiter_bonus.c \
					ft_lstmap_bonus.c \
					)

SRCSEXTRA	=		\
					$(addprefix $(SRC_DIR), \
					ft_atoi_base.c \
					ft_strisbase.c \
					ft_atoi_check.c \
					ft_strisnumber.c \
					ft_free_split.c \
					ft_max.c \
					ft_min.c \
					ft_strtoupper.c \
					ft_strtolower.c \
					ft_error.c \
					ft_atoi_err.c \
					ft_strjoinsep.c \
					)

OBJS	=			$(SRCS:.c=.o)

OBJSBONUS	=		$(SRCSBONUS:.c=.o)

OBJSEXTRA	=		$(SRCSEXTRA:.c=.o)

DPNDS	=			$(SRCS:.c=.d)

DPNDSBONUS	=		$(SRCSBONUS:.c=.o)

DPNDSEXTRA	=		$(SRCSEXTRA:.c=.d)

CC		=			gcc

RM		=			-rm -f

AR		=			ar rcs

CFLAGS	=			-Wall -Werror -Wextra -MD

NAME	=			libft.a
