NAME	= minishell

SRCS	= srcs/main.c srcs/builtin/cd.c srcs/builtin/echo.c srcs/builtin/env.c srcs/builtin/env1.c\
			srcs/builtin/exit.c srcs/builtin/export.c srcs/builtin/export_dop.c srcs/builtin/unset.c\
			srcs/execution/exec.c srcs/execution/exec_dop.c srcs/pipe/pipe.c\
			srcs/parser/parser_utils.c srcs/parser/parser.c srcs/parser/preparser.c srcs/parser/redirects.c\
			srcs/parser/stack_init.c srcs/parser/t_list_funcs.c srcs/parser/utils.c

HEADER	= -I./includes/minishell.h

OBJS	= ${SRCS:%.c=%.o}

CC		= gcc

RM		= rm -f

LIB		= -L./libft/ -lft

CFLAGS	= -Wall -Wextra -Werror ${HEADER}
#CFLAGS	= -I${HEADER}

RDLN	= /Users/snakita/.brew/Cellar/readline/8.1.2/

.PHONY:	all clean fclean re

.c.o:		${HEADER}
				${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
				@make -C ./libft/
				@${CC} ${CFLAGS} ${OBJS} -lreadline -L${RDLN}lib -o ${NAME}

all:		${NAME}

clean:
			@make fclean -C ./libft
			${RM} ${OBJS}

fclean:		clean
			@make fclean -C ./libft
			${RM} ${NAME}

re:			fclean all