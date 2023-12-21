NAME	= philo

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -Iinc/
LDFLAGS		= -lreadline
OBJS_DIR	= objs/

RED		= \033[1;31m
GREEN	= \033[1;32m
YELLOW	= \033[1;33m
BLUE	= \033[1;34m
RESET	= \033[0m

SRC =	src/main.c	\
		src/init.c	\
		src/utils.c	\
		src/core.c	\

OBJS = $(addprefix $(OBJS_DIR), $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(YELLOW)Compiling $(NAME)...$(RESET)"
	$(CC) $(OBJS) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled successfully!$(RESET)"

$(OBJS_DIR)%.o: %.c
	@echo "$(BLUE)Creating $(NAME) object files...$(RESET)"
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(RED)Cleaning $(NAME) object files...$(RESET)"
	rm -rf $(OBJS_DIR)

fclean: clean
	@echo "$(RED)Removing $(NAME) executable...$(RESET)"
	rm -f $(NAME)

re: fclean all