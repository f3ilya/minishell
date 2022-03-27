cmake_minimum_required(VERSION 3.21)
project(minishell C)

set(CMAKE_C_STANDARD 99)

add_executable(minishell main.c minishell.h exec.c exec_dop.c libft_utils.c ft_split.c pipe.c echo.c env.c cd.c unset.c env1.c utils.c)
