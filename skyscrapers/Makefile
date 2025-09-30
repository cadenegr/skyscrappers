# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/14 14:55:14 by cadenegr          #+#    #+#              #
#    Updated: 2025/09/30 17:21:46 by cadenegr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = skyscrapers

SRCDIR = src
OBJDIR = obj
LIBFTDIR = libft
MINILIBXDIR = minilibx-linux#added here

SRC_FILES = $(wildcard $(SRCDIR)/*.c)
#SRC = $(addprefix $(SRCDIR)/, $(SRC_FILES))
OBJ = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC_FILES))

LIBFT = $(LIBFTDIR)/libft_printf.a
INCLUDES = -I./include -I$(LIBFTDIR)

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -L$(LIBFTDIR) -lft_printf
RM = rm -rf

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIBFT) $(OBJDIR) $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(LIBFT):
	make -C $(LIBFTDIR)

clean:
	$(RM) $(OBJDIR)
	make -C $(LIBFTDIR) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFTDIR) fclean

re: fclean all

# Test targets
test: all
	@echo "Running comprehensive test suite..."
	@./tests/run_all_tests.sh

test-quick: all
	@echo "Running quick test suite..."
	@./tests/run_all_tests.sh --quick

test-functional: all
	@echo "Running functional tests..."
	@./tests/run_tests.sh

test-memory: all
	@echo "Running memory tests..."
	@./tests/run_memory_tests.sh

test-performance: all
	@echo "Running performance benchmarks..."
	@./tests/run_benchmarks.sh

.PHONY: all clean fclean re test test-quick test-functional test-memory test-performance


