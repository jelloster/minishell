# ----------FLAGS------------

FLAGS			:=	-Wall -Wextra -Werror
DEBUG_FLAGS		:=	-g
SANITIZE_FLAGS	:=	-g -fsanitize=address

# ------- COMPILER ----------

CC				:=	cc

# ------ SOURCE FILES -------

SRC_FILES		:=	main.c
OBJ_FILES		:=	$(SRC_FILES:.c=.o)
NAME			:=	fdf
LIBFT			:=	libft/libft.a

# ---------- MLX42 ----------

HEADERS			:=	-I $(MLX)/include -I libft/inc

# -------------RULES--------------

$(NAME): $(OBJ_FILES) $(LIBFT)
	$(CC) $(FLAGS) $(OBJ_FILES) $(LIBFT) $(LIBS) -o $@

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
