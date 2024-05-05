NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar
ARFLAGS = -rcs

SRC = ft_isalnum.c ft_isalpha.c ft_isascii.c \
		ft_isdigit.c ft_isprint.c ft_strlen.c ft_memset.c \
		ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c \
		ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
		ft_strncmp.c ft_strcmp.c ft_strrchr.c ft_memchr.c ft_memcmp.c \
		ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c \
		ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
		ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
		ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_putnbr_fd.c ft_lstlast.c ft_lstadd_back.c \
		ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c \
		ft_lstiter.c ft_lstmap.c \
		get_next_line.c \
		get_next_line_utils.c \
		ft_lstnew.c ft_lstadd_front.c ft_lstadd_back.c	 ### ADDED THIS LINE

BONUS_SRC = ft_lstsize.c ft_lstlast.c \
			ft_lstdelone.c ft_lstclear.c \
			ft_lstiter.c ft_lstmap.c 

### CHANGED TO MAKE LSTNEW, LSTADDFRONT, LSTADDBACK WITHOUT MAKE BONUS
# BONUS_SRC = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
# 		ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
# 		ft_lstclear.c ft_lstiter.c ft_lstmap.c 

.SILENT:

all: $(NAME)

OBJ = $(SRC:.c=.o)

BONUS_OBJ = $(BONUS_SRC:.c=.o)

message:
	@echo "$(LIGHT_BLUE)┌────────────────────────────────────────────────────────────────────────────┐$(DEFAULT)"
	@printf "$(LIGHT_BLUE)│Creating LIBFT......"

%.o: %.c message
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "$(LIGHT_BLUE)."

$(NAME): $(OBJ) ./libft.h
	$(AR) $(ARFLAGS) $(NAME) $(OBJ)
	@echo "$(LIGHT_BLUE)..Libft OK!│$(DEFAULT)"
	@echo "$(LIGHT_BLUE)└────────────────────────────────────────────────────────────────────────────┘$(DEFAULT)"
	@sleep 0.5

bonus: $(BONUS_OBJ) ./libft.h
		$(AR) $(ARFLAGS) $(NAME) $(BONUS_OBJ)

clean:
	rm -f $(OBJ) $(BONUS_OBJ) ./*.a ./*.o

fclean: clean
	rm -f $(NAME)

re: fclean all

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