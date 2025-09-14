# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/11 15:12:27 by macoulib          #+#    #+#              #
#    Updated: 2025/09/14 19:22:33 by macoulib         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC      = gcc
CFLAGS  = -Wall -Wextra -Werror 
RM      = rm -rf


NAME    = pipex

SRCS    = src/pipex.c \
          src/main.c

OBJS    = $(SRCS:.c=.o)

LIBFT   = librairie/libft/libft.a
PRINTF  = librairie/printf/ftprint/ft_print.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C librairie/libft

$(PRINTF):
	make -C librairie/printf/ftprint

clean:
	$(RM) $(OBJS)
	make clean -C librairie/libft
	make clean -C librairie/printf/ftprint

fclean: clean
	$(RM) $(NAME)
	make fclean -C librairie/libft
	make fclean -C librairie/printf/ftprint

re: fclean all

.PHONY: all clean fclean re
