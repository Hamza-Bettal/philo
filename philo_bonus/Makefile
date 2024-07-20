# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/10 08:55:53 by hbettal           #+#    #+#              #
#    Updated: 2024/07/18 16:47:38 by hbettal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g

NAME = philosophers_bonus

HEADER = philo_bonus.h

OBJ =	philo_bonus.o			parsing.o		philo_born_bonus.o		family_table.o

all: $(NAME)
	@echo "\033[1;32mCompilation Completed Successfully! ✅\033[0;m"

$(NAME) : $(OBJ) $(HEADER)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o : %.c $(HEADER)
	@echo "\033[0;34mCompiling $< .\033[0;m"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "\033[0;31mRemoving object files.\033[0;m"

	@echo "\033[0;31mRemoving object files.\033[0;m"

	@rm -f $(OBJ)
	@echo "\033[1;32mCleaning DONE ✅\033[0;m"

fclean: clean
	@echo "\033[0;31mRemoving program.\033[0;m"
	@echo "\033[1;32mDONE ✅\033[0;m"
	@rm -f $(NAME)

re: fclean all 

.PHONY: clean