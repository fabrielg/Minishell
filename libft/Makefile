# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/10 20:19:05 by gfrancoi          #+#    #+#              #
#    Updated: 2025/05/13 18:04:15 by gfrancoi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a

SRCS = \
	char/ft_has_char.c\
	char/ft_isalnum.c\
	char/ft_isalpha.c\
	char/ft_isascii.c\
	char/ft_isdigit.c\
	char/ft_isprint.c\
	char/ft_tolower.c\
	char/ft_toupper.c\
	gnl/get_next_line_utils.c\
	gnl/get_next_line.c\
	lst/ft_lstnew.c\
	lst/ft_lstadd_front.c\
	lst/ft_lstsize.c\
	lst/ft_lstlast.c\
	lst/ft_lstadd_back.c\
	lst/ft_lstdelone.c\
	lst/ft_lstclear.c\
	lst/ft_lstiter.c\
	lst/ft_lstmap.c\
	lst/ft_lstnb_find.c\
	lst2/ft_lstnew2.c\
	lst2/ft_lstadd_front2.c\
	lst2/ft_lstsize2.c\
	lst2/ft_lstlast2.c\
	lst2/ft_lstadd_back2.c\
	lst2/ft_lstdelone2.c\
	lst2/ft_lstclear2.c\
	lst2/ft_lstiter2.c\
	lst2/ft_lstmap2.c\
	lst2/ft_lstnb_find2.c\
	mem/ft_bzero.c\
	mem/ft_calloc.c\
	mem/ft_free_map.c\
	mem/ft_memchr.c\
	mem/ft_memcmp.c\
	mem/ft_memcpy.c\
	mem/ft_memmove.c\
	mem/ft_memset.c\
	nbr/ft_atoi_base.c\
	nbr/ft_atoi.c\
	nbr/ft_itoa.c\
	nbr/ft_max.c\
	nbr/ft_min.c\
	nbr/ft_nb_digits.c\
	nbr/ft_abs.c\
	printf/add_char.c\
	printf/add_nbr.c\
	printf/add_str.c\
	printf/add_unsigned.c\
	printf/ft_printf.c\
	printf/parsing.c\
	str/ft_split.c\
	str/ft_strarrlen.c\
	str/ft_strchr.c\
	str/ft_strdup.c\
	str/ft_striteri.c\
	str/ft_strjoin.c\
	str/ft_strlcat.c\
	str/ft_strlcpy.c\
	str/ft_strlen_char.c\
	str/ft_strlen.c\
	str/ft_strmapi.c\
	str/ft_strncmp.c\
	str/ft_strnstr.c\
	str/ft_strtol.c\
	str/ft_strrchr.c\
	str/ft_strtrim.c\
	str/ft_substr.c\
	str/ft_upper.c\
	str/ft_lower.c\
	strbuilder/ft_strbuilder_utils.c\
	strbuilder/ft_strbuilder.c\
	write/ft_putchar_fd.c\
	write/ft_putendl_fd.c\
	write/ft_putnbr_fd.c\
	write/ft_putstr_fd.c

OBJ_DIR = obj

OBJS = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(basename $(SRCS))))

all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $< -I.

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -fr $(OBJ_DIR)

fclean: clean
	rm $(NAME)

re: fclean all

.PHONY = all clean fclean re
