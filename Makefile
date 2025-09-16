# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/11 15:12:27 by macoulib          #+#    #+#              #
#    Updated: 2025/09/16 20:00:49 by macoulib         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC       = gcc
CFLAGS   = -Wall -Wextra -Werror -g
RM       = rm -f

NAME     = pipex
NAME_BONUS = pipex_bonus
SRCS_DIR = src
OBJS_DIR = objs

# Fichiers sources de la version standard
SRCS     = $(SRCS_DIR)/pipex.c \
           $(SRCS_DIR)/main.c


# Fichiers sources de la version bonus
SRCS_BONUS = $(SRCS_DIR)/pipex_bonus.c \
             $(SRCS_DIR)/main_bonus.c

# Fichiers objets de la version standard
OBJS     = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
DEPS     = $(OBJS:.o=.d)

# Fichiers objets de la version bonus
OBJS_BONUS = $(SRCS_BONUS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
DEPS_BONUS = $(OBJS_BONUS:.o=.d)

LIBFT    = librairie/ft_libft/libft.a
PRINTF   = librairie/printf/ftprint/libftprintf.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF) -o $(NAME)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT) $(PRINTF) -o $(NAME_BONUS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -MMD -c $< -o $@

$(LIBFT):
	make -C librairie/ft_libft

$(PRINTF):
	make -C librairie/printf/ftprint

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)
	$(RM) $(DEPS) $(DEPS_BONUS)
	make clean -C librairie/ft_libft
	make clean -C librairie/printf/ftprint

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)
	make fclean -C librairie/ft_libft
	make fclean -C librairie/printf/ftprint

re: fclean all

.PHONY: all bonus clean fclean re
-include $(DEPS) $(DEPS_BONUS)