NAME = philosophers
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g3
SRC = philosophers.c utils.c \
	init.c pars.c thread.c free.c
DEPS = inc/philosophers.h
ODIR = obj/
OBJ = $(SRC:%.c=$(ODIR)%.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME) : $(OBJ)
	@echo "compiling philosophers 🧙"
	@$(CC) $(OBJ) -o $(NAME)


$(ODIR)%.o: src/%.c Makefile $(DEPS) | $(ODIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(ODIR):
	@mkdir $(ODIR)

clean:
	@echo "clean all obj🔮"
	@rm -rf $(ODIR)

fclean: clean
	@echo "remove exe 🍄"
	@rm -rf $(NAME)

re: fclean all