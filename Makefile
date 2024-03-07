# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/01 08:38:42 by tkartasl          #+#    #+#              #
#    Updated: 2024/03/07 10:52:23 by vsavolai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFTD = ./libft

LIBFTA = $(LIBFTD)/libft.a

MAKE = make

CC = cc

RL_FLAGS = -lreadline -L ~/.brew/opt/readline/lib 

CFLAGS = -Wall -Wextra -Werror -g -Iincludes -I ~/.brew/opt/readline/include

SRCS = sources/minishell.c \
		sources/parse_commands.c \
		sources/parse_arguments.c \
		sources/parse_filename.c \
		sources/parse_redirections.c \
		sources/check_syntax.c \
		sources/parsing_errors.c \
		sources/helper_functions.c \
		sources/list_functions.c \
		sources/run_pipes.c \
		sources/ft_split_remix.c \
		sources/helper_functions2.c \
		sources/run_commands.c \
	#	sources/builtins.c \
	#	sources/builtins2.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFTA)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFTA) -o $(NAME) $(RL_FLAGS)

$(LIBFTA): 
	@$(MAKE) all -C $(LIBFTD)

clean:
	rm -f $(OBJS)
	@$(MAKE) clean -C $(LIBFTD)

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFTD)

re: fclean all

.PHONY: all clean fclean re