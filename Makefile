# ----------FLAGS------------

FLAGS			:=	-Wall -Wextra -Werror
DEBUG_FLAGS		:=	-g
SANITIZE_FLAGS	:=	-g -fsanitize=address

# ------- COMPILER ----------

CC				:=	cc

# ------ SOURCE FILES -------

SRC_FILES		:=	main.c			\
				parsing.c		\
				envp_utils.c		\
				cmd_split.c		\
				str_utils.c		\
				print_utils.c		\
				init_ms.c		\
				exe_cmd.c		\
				parsing_utils.c		\
				redirection_utils.c	\
				memory_functions.c	\
				history.c		\
				quote_utils.c		\
# ms_echo.c

# ------- PIPEX --------

PIPEX_PATH		:=	./pipex/
PIPEX_FILES		:=	awk_split.c	\
				error_utils.c	\
				pipex.c		\
				pipe_utils.c	\
				str_utils.c	\

PIPEX_SRC		:=	$(addprefix $(PIPEX_PATH), $(PIPEX_FILES))
PIPEX_OBJ		:=	$(PIPEX_SRC:.c=.o)


OBJ_FILES		:=	$(SRC_FILES:.c=.o) $(PIPEX_OBJ)
NAME			:=	minishell
LIBFT			:=	libft/libft.a

HEADERS			:=	-I libft/inc -I/usr/include/readline

# -------------RULES--------------

$(NAME): $(OBJ_FILES) $(LIBFT)
	$(CC) $(FLAGS) $(OBJ_FILES) $(LIBFT) -lreadline $(LIBS) -o $@  

$(OBJ_FILES): %.o : %.c
	$(CC) $(FLAGS) -c $< -o $@ $(HEADERS)

$(LIBFT):
	@make -C libft

# ----------- PHONIES ------------

.PHONY: all
all: $(NAME)

.PHONY: clean
clean:
	rm -f $(OBJ_FILES) 

.PHONY: fclean
fclean: clean
	rm -f $(NAME)
	@rm -rf

.PHONY: bonus
bonus : all

.PHONY: re
re: fclean all

.PHONY: mc
mc: all clean

.PHONY: debug
debug: FLAGS += $(DEBUG_FLAGS)
debug: re

.PHONY: sanitize
sanitize: FLAGS += $(SANITIZE_FLAGS)
sanitize: re
