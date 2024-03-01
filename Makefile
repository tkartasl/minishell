# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/01 08:38:42 by tkartasl          #+#    #+#              #
#    Updated: 2024/03/01 08:39:53 by tkartasl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFTD = ./libft

LIBFTA = $(LIBFTD)/libft.a

MAKE = make

CC = cc

CFLAGS = -Wall -Wextra -Werror -Iincludes

SRCS = sources/minishell.c \
		sources/parse_commands.c \
		sources/parse_arguments.c \
		sources/parse_filename.c \
		sources/parse_redirections.c \
		sources/check_syntax.c \
		sources/parsing_errors.c \
		sources/helper_functions.c \
		sources/list_functions.c \
	#	sources/builtins.c \
	#	sources/builtins2.c

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS) $(LIBFTA)
	$(MAKE) all -C $(LIBFTD)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFTA) -o $(NAME) -lreadline

$(LIBFTA): 
	$(MAKE) all -C $(LIBFTD)

clean:
	rm -f $(OBJS)
	@$(MAKE) clean -C $(LIBFTD)

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFTD)

re: fclean all

.PHONY: all clean fclean re