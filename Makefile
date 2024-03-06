# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aperron <aperron@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/21 07:09:43 by aperron           #+#    #+#              #
#    Updated: 2024/03/06 19:32:13 by aperron          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

########################### VARIABLES ############################

NAME		= philo

SRC_FOLDER	= ./src/

SRCS_BLANK	= main philo list utils init parse

SRCS		= $(addsuffix .c, $(addprefix $(SRC_FOLDER), $(SRCS_BLANK)))

FLAGS		= -g -Wall -Wextra -Werror

CC			= gcc

RM			= rm -f
RM_ALL		= rm -drf

TO_CLEAN	= *.dSYM *.o *test

RED="\033[0;31m"
NRM="\033[0m"

########################## TARGETS ###############################

all: $(NAME) run

$(NAME): $(SRCS)
	$(CC) $(FLAGS) $(SRCS) -o $@

test:
	@echo $(RED) "| Compiling \"$@\" without flags... |" $(NRM)
	@$(CC) $(SRCS) -o $@
	
run:
	@./$(NAME)

clean:
	@$(RM_ALL) $(TO_CLEAN)

fclean: clean
	@$(RM) $(NAME)
	
re: fclean all

.PHONY: all run clean fclean re test libft

###################################################################