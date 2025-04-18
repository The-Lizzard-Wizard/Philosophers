NAME = philosophers
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
SRC = philosophers.c
DEPS = inc/philosophers.h
ODIR = obj/
OBJ = $(SRC:%.c=$(ODIR)%.o)
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

.PHONY: all clean fclean re libft_comp

all: libft_comp $(NAME)

$(NAME) : $(OBJ) $(LIBFT)
	@echo "compiling philosophers 🧙"
	@$(CC) $(OBJ) $(LIBFT) -o $(NAME)

libft_comp :
	@$(MAKE) -s -C $(LIBFT_DIR)

$(ODIR)%.o: src/%.c Makefile $(DEPS) | $(ODIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(ODIR):
	@mkdir $(ODIR)

clean:
	@echo "clean all obj🔮"
	@rm -rf $(ODIR)
	@$(MAKE) -s -C $(LIBFT_DIR) clean

fclean: clean
	@echo "remove exe 🍄"
	@rm -rf $(NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean

re: fclean all