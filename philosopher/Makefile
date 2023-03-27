# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/22 12:49:44 by gyeon             #+#    #+#              #
#    Updated: 2022/03/04 18:07:58 by gyeon            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GCC = gcc
FLAGS = -Wall -Wextra -Werror
DIR_SRCS = ./philo/srcs/
DIR_SRCS_BONUS = ./philo_bonus/srcs_bonus/
DIR_HEADER = $(DIR_SRCS)header/
DIR_HEADER_BONUS = $(DIR_SRCS_BONUS)header/
DIR_TARGETS = ./targets/
TARGET = $(DIR_TARGETS)philo
TARGET_BONUS = $(DIR_TARGETS)philo_bonus
SRCS = main.c utils.c errhandler.c actions.c time.c \
	parsing.c pthreads.c mutexs.c set_philos.c mutex_print.c
SRCS_BONUS = main_bonus.c utils_bonus.c errhandler_bonus.c \
	actions_bonus.c time_bonus.c parsing_bonus.c routine_bonus.c \
	syscall_bonus.c set_philo_bonus.c sem_print_bonus.c
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all : $(TARGET) $(TARGET_BONUS)
man : $(TARGET)
bonus : $(TARGET_BONUS)
$(TARGET) : $(addprefix $(DIR_SRCS), $(OBJS))
	@mkdir -p $(DIR_TARGETS)
	$(GCC) $(FLAGS) -o $@ $^
$(TARGET_BONUS) : $(addprefix $(DIR_SRCS_BONUS), $(OBJS_BONUS))
	@mkdir -p $(DIR_TARGETS)
	$(GCC) $(FLAGS) -o $@ $^
%_bonus.o : %_bonus.c
	$(GCC) $(FLAGS) -c $< -o $@ -I $(DIR_HEADER_BONUS)
%.o : %.c
	$(GCC) $(FLAGS) -c $< -o $@ -I $(DIR_HEADER)
clean :
	rm -rf $(addprefix $(DIR_SRCS), $(OBJS)) $(addprefix $(DIR_SRCS_BONUS), $(OBJS_BONUS))
fclean : clean
	rm -rf $(TARGET) $(TARGET_BONUS)
	rm -rf $(DIR_TARGETS)
re : fclean all
.PHONY : all man bonus clean fclean