# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junykim <junykim@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/09 19:38:44 by junykim           #+#    #+#              #
#    Updated: 2022/12/04 17:55:43 by junykim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
CC		= CC
NAME	= philo
CFLAGS	= -Wextra -Wall -Werror
INC		= .
DEL		= rm -rf
ARC		= ar -rcs

# Colors
DEF_COLOR 	= \033[0;39m
GRAY 		= \033[0;90m
RED 		= \033[0;91m
GREEN 		= \033[0;92m
YELLOW 		= \033[0;93m
BLUE 		= \033[0;94m
MAGENTA 	= \033[0;95m
CYAN 		= \033[0;96m
WHITE 		= \033[0;97m

# Srcs
#-------MANDATORY--------
SRC_M_FILES = main \
			  init \
			  mtx \
			  thread \
			  thread_util \
			  thread_util2 \
			  thread_early_death \
			  profile \
			  util

SRCS = $(addsuffix .c, $(SRC_M_FILES))
OBJS = $(SRCS:%.c=%.o)

# Rules
all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) -pthread $(CFLAGS) $^ -o $@
	@echo "$(YELLOW)===============================================$(DEF_COLOR)"
	@echo "$(YELLOW)|    Philo mandatory compile finished.        |$(DEF_COLOR)"
	@echo "$(YELLOW)===============================================$(DEF_COLOR)"

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INC)
	@echo "$(YELLOW)===============================================$(DEF_COLOR)"
	@echo "$(YELLOW)|    	Philo mandatory compiling.....        |$(DEF_COLOR)"
	@echo "$(YELLOW)===============================================$(DEF_COLOR)"

clean :
	$(DEL) $(OBJS)
	@echo "$(CYAN)===============================================$(DEF_COLOR)"
	@echo "$(CYAN)|    	Philo mandatory clean finished.       |$(DEF_COLOR)"
	@echo "$(CYAN)===============================================$(DEF_COLOR)"

fclean : clean
	$(DEL) $(NAME)
	@echo "$(CYAN)===============================================$(DEF_COLOR)"
	@echo "$(CYAN)|  	  Philo mandatory fclean finished.    |$(DEF_COLOR)"
	@echo "$(CYAN)===============================================$(DEF_COLOR)"

re : 
	make fclean
	make all

.PHONY : all clean fclean re
