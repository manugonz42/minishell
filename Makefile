
# COLORS:
NC		=	\033[0m
LRED	=	\033[0;31m
LREDB	=	\033[1;31m
GREEN	=	\033[1;32m
LGREEN	=	\033[1;92m
PINK	=	\033[1;95m
YELLOW	=	\033[1;33m
BLUE	=	\033[1;34m
LBLUE	=	\033[1;36m

CC = gcc

INC_DIR = includes/
CFLAGS := -Wall -Wextra -Werror $(addprefix -I, $(INC_DIR))

SHELL := /bin/bash
UNAME := $(shell uname -s)

LDFLAGS = -lreadline #-lhistory

ifeq ($(UNAME), Linux)
LDFLAGS = -L/usr/local/lib -lreadline
endif

NAME = minishell

OBJS_PATH = objs/
SRC_PATH = src/
LIBFT_PATH = libft/
LIBFT = libft/libft.a
BUILT-INS = echo.c switch.c cd.c export.c unset.c exit.c
ENV = env_functions.c env_list.c
EXEC = functions.c redir.c exec.c files.c here_doc.c signal.c here_doc_utils.c
PARS = token_redir_set.c token_utils.c error.c token_list.c free_things.c\
		token_list_del.c pars.c pars_utils.c var_expand.c pars_utils_is.c \
		exit.c set_pack.c set_command.c set_token.c init_tokens.c command_utils.c
SRC = main.c print_functions.c print_funct_b.c
SRCS = $(addprefix src/exec/, $(EXEC)) \
	   $(addprefix src/parseo/, $(PARSEO)) \
	   $(addprefix src/built-ins/, $(BUILT-INS)) \
	   $(addprefix src/env/, $(ENV)) \
	   $(addprefix src/, $(SRC)) \
	   $(addprefix src/pars/, $(PARS)) \

OBJS = $(addprefix $(OBJS_PATH), $(SRCS:.c=.o))

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_PATH)

$(OBJS_PATH):
	@mkdir -p $(dir $(OBJS))
		@echo "**** [COMPILING MINICHELL...] ****"

$(OBJS_PATH)%.o: %.c | $(OBJS_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@
		@echo " $< ✔ "

$(NAME): $(LIBFT) $(OBJS_PATH) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $@ 
		@echo "**** [MINICHELL COMPILED] ****"

clean:
	make fclean -C $(LIBFT_PATH)
	rm -rf $(OBJS_PATH)
fclean: clean
	rm -rf $(NAME)

re: clean all

PHONY: all clean fclean re
