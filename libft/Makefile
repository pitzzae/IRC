#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/23 11:18:23 by gtorresa          #+#    #+#              #
#*   Updated: 2017/10/19 12:45:25 by gtorresa         ###   ########.fr       *#
#                                                                              #
#******************************************************************************#

NAME = libft.a
NAME32 = libft_i386.a
NAME64 = libft_x86_64.a

LIPO_LIB = lipo -create -output $@ $^
STD_LIB = mv $(NAME64) $(NAME)

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -s)
endif

ifeq ($(HOSTTYPE),Darwin)
	MAKE_LIB=$(LIPO_LIB)
else
	MAKE_LIB=$(STD_LIB)
endif

SRCS = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c\
	ft_isdigit.c ft_isprint.c ft_memalloc.c ft_memccpy.c ft_memchr.c\
	ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strcat.c ft_strchr.c\
	ft_strcmp.c ft_strcpy.c ft_strdup.c ft_strlcat.c ft_strlen.c ft_strncat.c\
	ft_strncmp.c ft_strncpy.c ft_strnstr.c ft_strrchr.c ft_strstr.c\
	ft_tolower.c ft_toupper.c ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c\
	ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c\
	ft_strnequ.c ft_strsub.c ft_strjoin.c ft_strtrim.c ft_strsplit.c ft_itoa.c\
	ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c ft_putchar_fd.c\
	ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c ft_lstdelone.c\
	ft_lstdel.c ft_lstadd.c ft_lstaddend.c ft_lstiter.c ft_lstmap.c\
	ft_lstsplit.c ft_lstprintstr.c ft_lstprintnbr.c ft_str_replace_chr.c\
	ft_lstlen.c ft_lstring.c ft_lstdup.c ft_strfocur.c get_next_line.c\
	ft_strjoin_free.c ft_realloc.c ft_tab_realloc.c ft_strocur.c ft_strlocur.c\
	ft_strcat_l.c ft_bufcpy.c ft_strisprint.c ft_strswap.c ft_date_time.c \
	ft_lst_env_new.c ft_lst_to_env.c ft_lst_get_env.c ft_lst_edit_env.c \
	ft_lst_add_env.c ft_lst_rm_env.c ft_strsplit_len.c ft_str_replace_str.c \
	ft_strsub_free.c ft_myputchar.c ft_lstaddend_free.c ft_udel.c \
	ft_strocur_slash.c ft_stradd_slash.c ft_tabdup.c ft_putbase.c \
	ft_puthex.c ft_swapuint32.c ft_swapuint8.c ft_putstr_whsp.c ft_pow.c \
	ft_putadd.c ft_strnocur.c ft_addchar_intstr.c

CFLAGS = -Wall -Wextra -Werror

INCLUDE	= -I./includes

O_DIR32 = ./obj_32

O_DIR64 = ./obj_64

OBJS32 = $(addprefix $(O_DIR32)/,$(SRCS:.c=.o))

OBJS64 = $(addprefix $(O_DIR64)/,$(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(NAME32) $(NAME64)
	@echo "\nCreating fat library."
	$(MAKE_LIB)

$(NAME32): $(OBJS32)
	@ar rc $@ $^
	@echo "\nCreating i386 archive library."
	@ranlib $@
	@echo "Indexing i386 archive library."

$(NAME64): $(OBJS64)
	@ar rc $@ $^
	@echo "\nCreating x86_64 archive library."
	@ranlib $@
	@echo "Indexing x86_64 archive library."

$(O_DIR64)/%.o: ./srcs/%.c
	@mkdir -p $(O_DIR64)
	@printf "."
	@gcc $(CFLAGS) -m64 -c $< $(INCLUDE) -o $@


$(O_DIR32)/%.o: ./srcs/%.c
	@mkdir -p $(O_DIR32)
	@printf "."
	@gcc $(CFLAGS) -m32 -c $< $(INCLUDE) -o $@

clean:
	@rm -rf $(O_DIR32)
	@rm -rf $(O_DIR64)
	@echo "Delete obj."

fclean: clean
	@rm -rf $(NAME) $(NAME32) $(NAME64)
	@echo "Delete $(NAME) $(NAME32) $(NAME64)."

re: fclean
	@make all
	@echo "Make library."

.PHONY: all clean fclean re
