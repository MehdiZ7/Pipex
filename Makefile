# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/02 12:23:46 by mzouhir           #+#    #+#              #
#    Updated: 2025/12/09 16:36:59 by mzouhir          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=pipex
SRCS=main.c parsing.c pipex_utils.c
OBJS=${SRCS:.c=.o}
CC=cc
CFLAGS= -Wall -Werror -Wextra
LIBFT_DIR=Libft
LIBFT=${LIBFT_DIR}/libft.a
INCLUDES = -I ${LIBFT_DIR} -I includes

all: ${LIBFT} ${NAME}
${LIBFT}:
	${MAKE} -C ${LIBFT_DIR}
${NAME}: ${OBJS} ${LIBFT}
	${CC} ${CFLAGS} ${OBJS} ${LIBFT} -o ${NAME}
%.o: %.c
	${CC} ${CFLAGS} ${INCLUDES} -c $< -o $@

clean:
	-rm -f ${OBJS} ${OBJS_BONUS}
	${MAKE} -C ${LIBFT_DIR} clean
fclean: clean
	-rm -f ${NAME}
	${MAKE} -C ${LIBFT_DIR} fclean
re: fclean all

.PHONY: all clean fclean re

SRCS_BONUS=	main_bonus.c parsing_bonus.c pipex_utils_bonus.c pipex_heredoc_bonus.c \
			get_next_line.c get_next_line_utils.c
OBJS_BONUS=${SRCS_BONUS:.c=.o}

bonus: ${LIBFT} ${OBJS_BONUS}
	${CC} ${CFLAGS} ${OBJS_BONUS} ${LIBFT} -o ${NAME}


clean_bonus:
	-rm -f ${OBJS_BONUS}
	${MAKE} -C ${LIBFT_DIR} clean
fclean_bonus: clean_bonus
	-rm -f ${NAME}
	${MAKE} -C ${LIBFT_DIR} fclean
re_bonus: fclean_bonus bonus

.PHONY: bonus clean_bonus fclean_bonus re_bonus



