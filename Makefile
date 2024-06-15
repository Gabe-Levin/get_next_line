# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: glevin <glevin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/03 16:20:22 by glevin            #+#    #+#              #
#    Updated: 2024/06/10 14:49:50 by glevin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Compiler
CC = cc
AR = ar
CFLAGS = -Wall -Wextra -Werror
ARFLAGS = rcs

#Library name
NAME = libftprintf.a

#Source Files
SRCS = get_next_line.c

#Object Files
OBJS = $(SRCS:.c=.o)

#Default Target: Build the library
all: $(NAME)

#Rule to create the library
$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $^

#Rule to compile .c files to .o files
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ && echo "\033[32m✔\033[0m $< compiled successfully"

#Clean up object files
clean:
	@rm -f $(OBJS) && echo "\033[31m🗑️\033[0m  Object files removed"

#Clean up objects files and the library
fclean: clean
	@rm -f $(NAME) && echo "\033[31m🗑️\033[0m  Library removed"

#Rebuild the library
re: fclean all

.PHONY: all clean fclean re