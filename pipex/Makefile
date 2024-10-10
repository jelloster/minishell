# ------------ NAME --------------
NAME	:=	pipex

# ---------- COMPILER ------------
CC	:=	cc

# ----------- FLAGS --------------
FLAGS	:=	-Wall -Wextra -Werror

LIBFT	:=	libft/libft.a

# -------- SOURCE FILES ----------
SRC	:=	main.c		\
		awk_split.c	\
		error_utils.c	\
		pipex.c		\
		pipe_utils.c	\
		str_utils.c	\
		cmd_utils.c	\

OBJ	:= 	$(SRC:.c=.o)

# -------------RULES--------------
 

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(FLAGS) $(LIBFT) -o $@ $^

%.o : %.c
	$(CC) $(FLAGS) -c $< -o $@

$(LIBFT):
	@make -C libft

# ----------- PHONIES ------------

.PHONY: all
all: $(NAME)

.PHONY: clean
clean:
	rm -f $(OBJ) $(OBJ) .bonus

.PHONY: fclean
fclean: clean
	rm -f $(NAME) .bonus

.PHONY: re
re: fclean all

.PHONY: bonus
bonus: .bonus
