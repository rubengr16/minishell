-include vbles.mk

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(NAME): $(OBJS) $(OBJSEXTRA)
	$(AR) $(NAME) $(OBJS) $(OBJSEXTRA)

clean:
	$(RM) $(OBJS) $(DPNDS) $(OBJSBONUS) $(DPNDSBONUS) $(OBJSEXTRA) $(DPNDSEXTRA)

fclean: clean
	$(RM) $(NAME)

bonus: $(OBJSBONUS)
	$(AR) $(NAME) $(OBJSBONUS)

re:	fclean all

.PHONY: all clean fclean bonus re
