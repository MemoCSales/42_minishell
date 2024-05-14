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
		./utils/cleanup_2.c \
		./parsing/parse_utils/1_args.c \
		./parsing/parse_utils/2_input_handling.c \
		./parsing/parse_utils/3_redirection_and_variables.c \
		./parsing/parse_utils/4_quotes.c \
		./parsing/parse_utils/5_command_processing.c \
		./parsing/parse_utils/6_pipe_and_redirection.c \
		./parsing/parse_utils/7_string_manipulation.c \
		./parsing/parse_utils/8_is_and_prints.c \
		./parsing/parse_utils/9_checkers_and_counters.c \
		./parsing/parse_utils/10_placeholder_1.c \
		./parsing/parse_utils/11_placeholder_2.c \
		./parsing/parse_utils/parse_test.c \
		./buildins/buildins.c \
		./buildins/cd.c \
		./buildins/env.c \
		./buildins/pwd.c \
		./buildins/unset.c \
		./buildins/export.c \
		./buildins/echo.c \
		./parsing/parse.c \
		./execution/exec.c \
		./execution/exec_utils.c \

all: $(NAME)
	@./minishell

OBJ = $(patsubst %.c, $(OBJ_DIR)%.o, $(SRC))

$(LIBFT):
		@make -C $(LIBFT_DIRECTORY)

$(NAME): $(OBJ) $(LIBFT)
			@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)
			@echo "$(RED)┌──────────────────────────────────────────────────────────────────────────┐$(DEFAULT)"
			@echo "$(RED)│.. .   .    .     .        Welcome to MiniℍΞLL         .     .    .   . ..│$(DEFAULT)"
			@echo "$(RED)└──────────────────────────────────────────────────────────────────────────┘$(DEFAULT)"
			@# @echo "$(RED)┌──────────────────────────────────────────────────────────────────────────┐$(DEFAULT)"
			@# @echo "$(RED)│                       ⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠩⠭⠙⠀⠀⠀⠀                       │"
			@# @echo "$(RED)│                       ⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⣿⣷⣮⠀⠀⠀⠀⠀⠀⢀⣴⣾⣿⣿⣦⠀⠀⠀                       │"
			@# @echo "$(RED)│                       ⠀⠀⠀⠀⠀⠀⠀⣻⣿⣿⣿⣿⣿⠂⠀⠀⠀⠀⠀⠈⣿⣿⣿⣿⣿⣷⠀⠀                       │"
			@# @echo "$(RED)│                       ⠀⠀⠀⠀⠀⠀⣠⣿⣿⣿⣿⣿⠋⠀⠀⠀⠀⠀⠀⠀⢙⣿⣿⣿⣿⣿⣴⣶                       │"
			@# @echo "$(RED)│                       ⠀⠀⠀⠀⠀⠀⣾⣿⣿⣿⢸⣧⠁⠀⠀⠀⠀⠀⠀⠀⢀⣽⣧⣿⣿⣿⣿⣿                       │"
			@# @echo "$(RED)│                       ⠀⡀⠀⠀⠀⠀⢸⣿⣿⣿⣸⣿⣷⣄⠀⠀⠀⠀⠀⣰⣿⣿⢸⣿⣿⣿⣿⣿                       │"
			@# @echo "$(RED)│                       ⠀⠈⠫⠂⠀⠀⠊⣿⢿⣿⡏⣿⠿⠟⠀⠀⠀⠀⠈⠿⠿⣿⢸⣿⣿⣿⠛⠋                       │"
			@# @echo "$(RED)│                       ⠀⠀⠀⠀⠱⡀⠈⠁⠀⢝⢷⡸⡇⠀⠀⠀⠀⠀⠀⠀⢹⢣⡿⡙⠀⠉⠀⠀                       │"
			@# @echo "$(RED)│                       ⠀⠀⠀⠀⢀⠇⠀⠀⢀⣾⣦⢳⡀⠀⠀⠀⠀⠀⠀⠀⢀⢟⣼⣧⡀⠀⠀⠀                       │"
			@# @echo "$(RED)│                       ⠀⠀⠀⢀⠎⠀⢀⣴⣿⣿⣿⡇⣧⠀⠀⠀⠀⠀⠀⠀⡾⣼⣿⣿⣿⡄⠀⠀                       │"
			@# @echo "$(RED)│                       ⠀⢀⡔⠁⠀⢠⡟⢻⡻⣿⣿⣿⣌⡀⠀⠀⠀⠀⠀⢘⣠⣿⣿⣿⢟⠇⠀⠀                       │"
			@# @echo "$(RED)│                       ⢀⡎⠀⠀⠀⣼⠁⣼⣿⣦⠻⣿⣿⣷⡀⠀⠀⠀⢠⣿⣿⣿⢏⣴⣿⣇⠀⠀                       │"
			@# @echo "$(RED)│                       ⢸⠀⠀⠀⠀⡟⢰⣿⣿⡟⠀⠘⢿⣿⣷⡀⠀⢠⣿⣿⡿⠁⠀⢿⣿⣿⠀⠀                       │"
			@# @echo "$(RED)│                       ⠈⠳⠦⠴⠞⠀⢸⣿⣿⠁⠀⠀⠀⠹⣿⡧⠀⣾⣿⠏⠀⠀⠀⠘⣿⣿⠀⠀                       │"
			@# @echo "$(RED)│                       ⠀⠀⠀⠀⠀⠀⢸⣿⡇⠀⠀⠀⠀⢰⣿⡇⠀⢿⣿⡀⠀⠀⠀⠀⣽⣿⡄⠀                       │"
			@# @echo "$(RED)│                       ⠀⠀⠀⠀⠀⠀⢸⣿⡇⠀⠀⠀⠀⢸⣿⡇⠀⢸⣿⡇⠀⠀⠀⠀⢸⣿⡇⠀                       │"
			@# @echo "$(RED)│                       ⠀⠀⠀⠀⠀⠀⢸⣿⠁⠀⠀⠀⠀⢸⣿⡇⠀⢸⣿⠃⠀⠀⠀⠀⢸⣿⠇⠀                       │"
			@# @echo "$(RED)│                       ⠀⠀⠀⠀⠀⠀⠀⣿⠀⠀⠀⠀⠀⠀⣿⡇⠀⢸⡿⠀⠀⠀⠀⠀⢸⡟⠀⠀                       │"
			@# @echo "$(RED)│                       ⠀⠀⠀⠀⠀⠀⠀⣿⣆⠀⠀⠀⠀⠀⣿⣧⠀⣿⣧⠀⠀⠀⠀⠀⣼⣧⠀⠀                       │"
			@# @echo "$(RED)│                       ⠀⠀⠀⠀⠀⠀⠀⠏⢿⠄⠀⠀⠀⠐⢸⣿⠀⣿⠇⠀⠀⠀⠀⢰⡿⠋⠀⠀                       │"
			@# @echo "$(RED)│                       ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠀⠁⠀                       │"
			@# @echo "$(RED)│                         <=--Ψψ  $(LIGHT_RED)miniℍΞLL  $(RED)ψΨ--=>                         │"
			@# @echo "$(RED)└──────────────────────────────────────────────────────────────────────────┘$(DEFAULT)"

$(OBJ_DIR)%.o: %.c
			@mkdir -p $(@D)
			@$(CC) $(CFLAGS) -I$(LIBFT_DIRECTORY) -c $< -o $@
# CHANGED clean AND fclean SO THE make re DOES NOT DELETE THE LIBFT (FASTER RECOMPILATION)
clean:
		@rm -rf $(OBJ_DIR)
		@# @make clean -C $(LIBFT_DIRECTORY)///
		@echo "$(RED)┌──────────────────────────────────────────────────────────────────────────┐$(DEFAULT)"
		@echo "$(RED)│                          Object files deleted!                           │$(DEFAULT)"

fclean: clean
		@rm -f ./$(NAME)
		@# @rm -f ./$(LIBFT)///
		@echo "$(RED)│                          All  files   deleted!                           │$(DEFAULT)"
		@echo "$(RED)└──────────────────────────────────────────────────────────────────────────┘$(DEFAULT)"

cleanlib:
		@make clean -C $(LIBFT_DIRECTORY)
		@rm -f ./$(LIBFT)

fre: fclean cleanlib all #TO DELETE THE LIBFT AND RECOMPILE IT

re: fclean all
	@# @./minishell

norminette: 
		norminette $(SRC) minishell.h $(LIBFT_DIRECTORY)

va:
		valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=all ./minishell
		

.PHONY: all clean fclean re

LIGHT_RED = \033[1;31m
RED = \033[0;31m
DARK_RED = \033[0;35m
GREEN = \033[1;32m
YELLOW = \033[1;33m
LIGHT_CYAN = \033[1;36m
CYAN = \033[0;36m
LIGHT_BLUE = \033[1;34m
DARK_BLUE = \033[0;34m
DEFAULT = \033[0m