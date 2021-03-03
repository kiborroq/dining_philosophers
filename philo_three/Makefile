# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/27 18:20:28 by kiborroq          #+#    #+#              #
#    Updated: 2021/03/03 20:21:55 by kiborroq         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo_three
SRCS_DIR	= srcs/
SRCS		= ${SRCS_DIR}philo_three.c \
			${SRCS_DIR}init_game.c \
			${SRCS_DIR}processes_threads.c \
			${SRCS_DIR}routine.c \
			${SRCS_DIR}close_game.c \
			${SRCS_DIR}print.c \
			${SRCS_DIR}time.c \
			${SRCS_DIR}utils.c \
			${SRCS_DIR}init_game_utils.c
OBJS		= ${SRCS:.c=.o}
INCL		= includes/
CC			= gcc
CFLAGS		= -Werror -Wextra -Wall
PTHREAD		= -pthread

.c.o :
			@${CC} -c $< -o ${<:.c=.o} -I ${INCL}

${NAME} : 	${OBJS}
			@echo Create ${NAME}
			@${CC} ${PTHREAD} ${OBJS} -o ${NAME}

all :		${NAME}

clean :
			@echo Remove all *.o
			@rm -f ${OBJS}

fclean : 	clean
			@echo Remove ${NAME}
			@rm -f ${NAME}

re : 		fclean all

.PHONY: 	all clean fclean re .c.o test
