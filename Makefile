# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/11 15:12:27 by macoulib          #+#    #+#              #
#    Updated: 2025/09/14 14:36:16 by macoulib         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# Compilateur et flags
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror 
RM      = rm -rf

# Nom du binaire
NAME    = pipex

# Sources de ton projet
SRCS    = src/pipex.c \
          src/main.c

# Objets
OBJS    = $(SRCS:.c=.o)

# Librairies
LIBFT   = librairie/libft/libft.a
PRINTF  = librairie/printf/ftprint/ft_print.a

# Règle principale
all: $(NAME)

# Compilation du binaire
$(NAME): $(OBJS) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF) -o $(NAME)

# Compilation des .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compilation des librairies
$(LIBFT):
	make -C librairie/libft

$(PRINTF):
	make -C librairie/printf/ftprint

# Nettoyage
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
