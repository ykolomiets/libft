# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/10 20:24:37 by ykolomie          #+#    #+#              #
#    Updated: 2018/10/17 21:25:55 by ykolomie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME :=			libft.a

SRC_DIR :=		./src
INC_DIR :=		./includes
OBJ_DIR :=		./obj

HEADERS :=		libft.h			\
				printf_core.h					\
				dragon4.h						\
				big_int.h						\
				float_to_integer_conversion.h	

HEADERS_DEP :=	$(addprefix $(INC_DIR)/, $(HEADERS))

SRC :=			ft_memset.c		\
				ft_bzero.c		\
				ft_memcpy.c		\
				ft_memmove.c	\
				ft_memchr.c		\
				ft_memcmp.c		\
				ft_memccpy.c	\
				ft_strlen.c		\
				ft_strdup.c		\
				ft_strcpy.c		\
				ft_strncpy.c	\
				ft_strcat.c		\
				ft_strlcat.c	\
				ft_strchr.c		\
				ft_strrchr.c	\
				ft_strstr.c		\
				ft_strnstr.c	\
				ft_strcmp.c		\
				ft_strncmp.c	\
				ft_atoi.c		\
				ft_isalpha.c	\
				ft_isdigit.c	\
				ft_isalnum.c	\
				ft_isascii.c	\
				ft_isprint.c	\
				ft_toupper.c	\
				ft_tolower.c	\
				ft_memalloc.c	\
				ft_memdel.c		\
				ft_strnew.c		\
				ft_strdel.c		\
				ft_strclr.c		\
				ft_striter.c	\
				ft_striteri.c	\
				ft_strmap.c		\
				ft_strmapi.c	\
				ft_strequ.c		\
				ft_strnequ.c	\
				ft_strsub.c		\
				ft_strjoin.c	\
				ft_strtrim.c	\
				ft_strsplit.c	\
				ft_itoa.c		\
				ft_putchar.c	\
				ft_putstr.c		\
				ft_putendl.c	\
				ft_putnbr.c		\
				ft_putchar_fd.c	\
				ft_putstr_fd.c	\
				ft_putendl_fd.c	\
				ft_putnbr_fd.c	\
				ft_lstnew.c		\
				ft_lstdelone.c	\
				ft_lstdel.c		\
				ft_lstadd.c		\
				ft_lstiter.c	\
				ft_lstmap.c		\
				ft_strncat.c	\
				ft_free_table.c \
				ft_strupcase.c	\
				ft_strlowcase.c	\
				ft_atoi_base.c	\
				ft_count_word.c	\
				ft_ceil.c		\


PRINTF_SRC :=	ft_printf.c						\
				ft_dprintf.c					\
				ft_snprintf.c					\
				ft_vdprintf.c					\
				ft_vsnprintf.c					\
				wchartobuf.c					\
				printf_core.c					\
				flags.c							\
				length.c						\
				precision.c						\
				length_modifier.c				\
				specifier.c						\
				print_integer_part1.c			\
				print_integer_part2.c			\
				print_integer_part3.c			\
				print_float_part1.c	    		\
				print_float_part2.c	    		\
				print_percent.c					\
				print_char.c					\
				print_string.c					\
				print_pointer.c					\
				print_none_specifier.c			\
				print_left_adjust.c             \
				log_base_2.c					\
				big_int.c						\
				big_int_power_of_10.c			\
				big_int_addition.c				\
				big_int_multiplication.c		\
				big_int_multiplication_by_int.c	\
				big_int_exponentiation.c		\
				big_int_division.c				\
				big_int_shift_left.c			\
				float64_to_integer_conversion.c	\
				dragon4_core.c					\
				dragon4_core_start_value.c      \
				dragon4_core_rounding.c         \
				dragon4_format_positional.c		\
				dragon4_format_scientific.c		\
				dragon4_print_float64.c			\
				dragon4_print_inf_nan.c			\

SRC +=			$(PRINTF_SRC)

OBJ =			$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

CC =			clang
CC_FLAGS =		-Wall -Wextra -Werror
INC_FLAGS =		-I $(INC_DIR)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c $(HEADERS_DEP)
	$(CC) $(FLAGS) $(INC_FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: clean all

vpath %.c		$(SRC_DIR)	\
				$(SRC_DIR)/printf	

.PHONY: all check clean fclean re
