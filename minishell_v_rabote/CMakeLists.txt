cmake_minimum_required(VERSION 3.21)
project(minishell C)

set(CMAKE_C_STANDARD 99)

add_executable(minishell exec.c minishell.h exec_dop.c main.c libft_utils.c ft_split.c)
