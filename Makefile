# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/23 21:59:27 by dohelee           #+#    #+#              #
#    Updated: 2021/12/06 19:48:48 by dohelee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang++
CFLAGS = -std=c++98 -g -Wall -Wextra -Werror -fsanitize=address

NAME = test

SRCS_DIR = srcs/
#SRCS =  main.cpp // doesn't work on mac
SRCS =  vector_performance.cpp
#SRCS =  map_performance.cpp 

OBJS_DIR = 	objs/
OBJ = $(SRCS:.cpp=.o)
OBJS = $(addprefix $(OBJS_DIR), $(OBJ))

$(OBJS_DIR)%.o : $(SRCS_DIR)%.cpp
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $^ -o $@

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all	: $(NAME)

clean :
	rm -rf $(OBJS_DIR)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re
