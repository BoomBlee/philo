# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kcaraway <kcaraway@student.21-school.r>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/16 02:50:17 by kcaraway          #+#    #+#              #
#    Updated: 2021/01/16 03:24:23 by kcaraway         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_three
CC = gcc
CFLAGS = -Wall -Wextra -Werror

FILE = \
function_eat_think_sleep \
function_stop_death \
main \
malloc_init \
pars \
delete

SRCS = $(addsuffix .c,$(FILE))

BINS = $(addsuffix .o,$(FILE))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(BINS)
	@$(CC) $(CFLAGS) -o $(NAME) $(BINS)
	@clear
	@echo "\033[32m$(NAME) created\033[0m"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	@rm -f $(BINS)
	@clear
	@echo "\033[33mclean completed\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[31mfclean completed\033[0m"

re: fclean all