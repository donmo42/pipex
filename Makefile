CC       = gcc
CFLAGS   = -Wall -Wextra -Werror -g
RM       = rm -f

NAME     = pipex
NAME_BONUS = pipex_bonus
SRCS_DIR = src
SRCS_DBONUS = src_bonus
OBJS_DIR = objs

# Fichiers sources de la version standard
SRCS     = $(SRCS_DIR)/pipex.c \
           $(SRCS_DIR)/main.c

# Fichiers sources de la version bonus
SRCS_BONUS = $(SRCS_DBONUS)/pipex_bonus.c \
             $(SRCS_DBONUS)/main_bonus.c

# Fichiers objets de la version standard
OBJS     = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
DEPS     = $(OBJS:.o=.d)

# Fichiers objets de la version bonus
OBJS_BONUS = $(SRCS_BONUS:$(SRCS_DBONUS)/%.c=$(OBJS_DIR)/%.o)
DEPS_BONUS = $(OBJS_BONUS:.o=.d)

LIBFT    = librairie/ft_libft/libft.a
PRINTF   = librairie/printf/ftprint/libftprintf.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF) -o $(NAME)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT) $(PRINTF) -o $(NAME_BONUS)

# Règle pour les objets de la version standard
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -MMD -c $< -o $@

# Règle pour les objets de la version bonus
$(OBJS_DIR)/%.o: $(SRCS_DBONUS)/%.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -MMD -c $< -o $@

# Compilation de libft
$(LIBFT):
	make -C librairie/ft_libft

# Compilation de printf
$(PRINTF):
	make -C librairie/printf/ftprint

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)
	$(RM) $(DEPS) $(DEPS_BONUS)
	rm -rf $(OBJS_DIR)
	make clean -C librairie/ft_libft
	make clean -C librairie/printf/ftprint

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)
	rm -rf $(OBJS_DIR)
	make fclean -C librairie/ft_libft
	make fclean -C librairie/printf/ftprint

re: fclean all

.PHONY: all bonus clean fclean re
-include $(DEPS) $(DEPS_BONUS)