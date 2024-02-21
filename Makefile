NAME = minishell
LIBFTD = ./libft
LIBFTA = $(LIBFTD)/libft.a
MAKE = make
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes
OBJSD = ./objs

SRCS = sources/minishell.c \
		sources/parsing.c \
		sources/builtins.c \
		sources/builtins2.c

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
		$(MAKE) all -C $(LIBFTDIR)
		$(CC) $(CFLAGS) $(OBJS) ./libft/libft.a -o $(NAME)

clean:
		rm -f $(OBJS)
		@$(MAKE) clean -C $(LIBFTDIR)

fclean: clean
		@rm -f $(NAME)
		@rm -f libft.a
		@$(MAKE) fclean -C $(LIBFTDIR)

re: fclean all

.PHONY: all clean fclean re