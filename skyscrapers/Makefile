# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/14 14:55:14 by cadenegr          #+#    #+#              #
#    Updated: 2024/03/13 22:31:37 by cadenegr         ###   ########.fr        #
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


