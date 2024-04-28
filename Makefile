NAME	= minishell

LIBFT_DIRECTORY  = ./libft/
LIBFT	= $(LIBFT_DIRECTORY)libft.a

OBJ_DIR	= obj/
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g

SRC =	main.c \
		minishell.c \
		./utils/init_env.c \
		./utils/cleanup.c \
		./utils/print_struct.c \
		./buildins/buildins.c \
		./buildins/cd.c \
		./buildins/env.c \
		./buildins/pwd.c \
		./buildins/unset.c \
		./buildins/export.c \
		./buildins/echo.c \
		./parsing/parse.c \
		./execution/exec.c \

##ADDED FOR TEST PARSER
SRC2 = 	parsing_2/parser.c \
		parsing_2/parse_utils.c \

OBJ2 = $(patsubst %.c, $(OBJ_DIR)%.o, $(SRC2))
##END OF ADDITION

all: $(NAME)

OBJ = $(patsubst %.c, $(OBJ_DIR)%.o, $(SRC))

$(LIBFT):
		make -C $(LIBFT_DIRECTORY)

$(NAME): $(OBJ) $(LIBFT)
			$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)
			@echo "$(GREEN)$(NAME) created!$(DEFAULT)"

$(OBJ_DIR)%.o: %.c
			@mkdir -p $(@D)
			@$(CC) $(CFLAGS) -I$(LIBFT_DIRECTORY) -c $< -o $@

##ADDED FOR TEST PARSER
parser: $(OBJ2) $(LIBFT)
		$(CC) $(CFLAGS) $(OBJ2) $(LIBFT) -lreadline -o parser
		@echo "$(GREEN)Parser created!$(DEFAULT)"
##END OF ADDITION

clean:
		rm -rf $(OBJ_DIR)
		@make clean -C $(LIBFT_DIRECTORY)
		@echo "$(YELLOW)Object files deleted!$(DEFAULT)"

fclean: clean
		@rm -f ./parser
		@rm -f ./$(NAME)
		@rm -f ./$(LIBFT)
		@echo "$(RED)All files deleted!$(DEFAULT)"

re: fclean all

norminette: 
		norminette $(SRC) $(SRC2) $(SUPPORT_DIR) $(SRC2) minishell.h $(LIBFT_DIRECTORY)

valgrind:
		valgrind --leak-check=full --show-leak-kinds=all ./minishell

.PHONY: all clean fclean re

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m