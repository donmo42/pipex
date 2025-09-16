# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/11 15:12:27 by macoulib          #+#    #+#              #
#    Updated: 2025/09/16 17:04:00 by macoulib         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC       = gcc
CFLAGS   = -Wall -Wextra -Werror -g
RM       = rm -f
AR       = ar -rcs

NAME     = pipex
SRCS_DIR = src
OBJS_DIR = objs
INCS_DIR = includes

SRCS     = $(SRCS_DIR)/pipex.c \
           $(SRCS_DIR)/main.c

OBJS     = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
DEPS     = $(OBJS:.o=.d)

LIBFT    = librairie/ft_libft/libft.a
PRINTF   = librairie/printf/ftprint/libftprintf.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF) -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -MMD -c $< -o $@

$(LIBFT):
	make -C librairie/ft_libft

$(PRINTF):
	make -C librairie/printf/ftprint

clean:
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror 
RM      = rm -rf


NAME    = pipex

SRCS    = src/pipex.c \
          src/main.c

OBJS    = $(SRCS:.c=.o)

LIBFT   = librairie/ft_libft/libft.a
PRINTF  = librairie/printf/ftprint/libftprintf.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C librairie/ft_libft

$(PRINTF):
	make -C librairie/printf/ftprint

clean:
	$(RM) $(OBJS)
	make clean -C librairie/ft_libft
	make clean -C librairie/printf/ftprint

fclean: clean
	$(RM) $(NAME)
	make fclean -C librairie/ft_libft
	make fclean -C librairie/printf/ftprint

re: fclean all

.PHONY: all clean fclean re

	$(RM) $(OBJS) $(DEPS)
	make clean -C librairie/ft_libft
	make clean -C librairie/printf/ftprint

fclean: clean
	$(RM) $(NAME)
	make fclean -C librairie/ft_libft
	make fclean -C librairie/printf/ftprint

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re