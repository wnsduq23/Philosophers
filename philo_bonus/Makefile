# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junykim <junykim@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/22 14:50:30 by junykim           #+#    #+#              #
#    Updated: 2022/12/22 14:50:35 by junykim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= philo_bonus
CFLAGS 		= -Wall -Wextra -Werror
CC 			= cc
SRC 		= philo_main_bonus.c philo_utils_1_bonus.c philo_utils_2_bonus.c philo_action_bonus.c philo_action_utils_1.bonus.c
OBJ 		= $(SRC:.c=.o)

ifdef WITH_BONUS
	OBJ_FILES = $(BONUS_OBJ)
	SRC_FILES = $(BONUS_SRC)
else
	OBJ_FILES = $(OBJ)
	SRC_FILES = $(SRC)
endif

all : $(NAME)

$(NAME) : $(OBJ_FILES)
	$(CC) -pthread $(CFLAGS) -o $(NAME) $(SRC)

$(OBJ_FILES) : $(SRC_FILES)
	$(CC) $(CFLAGS) -c $(SRC_FILES)

clean :
	rm -f $(OBJ_FILES) $(BONUS_OBJ)

fclean :
	rm -f $(OBJ_FILES) $(BONUS_OBJ) $(NAME)

re :
	$(MAKE) fclean
	$(MAKE) all
