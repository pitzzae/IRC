#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/05 22:20:23 by gtorresa          #+#    #+#              #
#*   Updated: 2017/11/08 04:06:53 by gtorresa         ###   ########.fr       *#
#                                                                              #
#******************************************************************************#

SERVER			= server
CLIENT			= client
CC				= gcc

CFLAGS			= -g3 -Wall -Werror -fsanitize=address -fsanitize=undefined

LIBFT_DIR		= ./libft
LIBFT_NAME		= $(LIBFT_DIR)/libft.a
INCL_DIR		= -I./includes -I$(LIBFT_DIR)/includes
INCL_LIB		= -L./libft -lft

OBJS_DIR_SER	= objs_server
OBJS_DIR_CLI	= objs_client

SERVER_SRCS_DIR	= srcs/server
CLIENT_SRCS_DIR	= srcs/client

SERVER_SRCS		= main.c init_env.c clean_fd.c get_opt.c x.c main_loop.c \
				init_fd.c do_select.c check_fd.c srv_create.c srv_accept.c \
				client_read.c client_write.c ft_irc_cmd_nick.c \
				ft_irc_cmd_user.c ft_irc_cmd_who.c ft_irc_error.c \
				ft_irc_print.c ft_irc_motd.c ft_parse_irc_cmd.c \
				ft_irc_cmd_quit.c ft_send.c ft_irc_cmd_join.c \
				ft_irc_cmd_leave.c ft_irc_create_chanel.c ft_irc_get_chanel.c \
				ft_irc_cmd_chanel.c ft_irc_clear_empty_chanel.c

CLIENT_SRCS		= main.c

SERVER_OBJECTS	= $(patsubst %.c, $(OBJS_DIR_SER)/%.o, $(SERVER_SRCS))
CLIENT_OBJECTS	= $(patsubst %.c, $(OBJS_DIR_CLI)/%.o, $(CLIENT_SRCS))


.PHONY: all

all: ${SERVER}
	@echo "\nAll Done"

$(SERVER): makelib $(SERVER_OBJECTS)
	@$(CC) $(SERVER_OBJECTS) -o $@ $(CFLAGS) $(INCL_DIR) $(INCL_LIB)

$(OBJS_DIR_SER)/%.o: $(addprefix $(SERVER_SRCS_DIR)/,%.c)
	@mkdir -p $(OBJS_DIR_SER)
	@$(CC) -c -o $@ $(CFLAGS) $^ $(INCL_DIR)
	@printf "."

$(CLIENT): makelib $(CLIENT_OBJECTS)
	@$(CC) $(CLIENT_OBJECTS) -o $@ $(CFLAGS) $(INCL_DIR) $(INCL_LIB)

$(OBJS_DIR_CLI)/%.o: $(addprefix $(CLIENT_SRCS_DIR)/,%.c)
	@mkdir -p $(OBJS_DIR_CLI)
	@$(CC) -c -o $@ $(CFLAGS) $^ $(INCL_DIR)
	@printf "."

makelib: 
	@echo "Make libft"
	@make -j 8 -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(SERVER)
	@rm -f $(CLIENT)
	@make fclean -j 8 -C $(LIBFT_DIR)
	@echo "Delete bin"

clean:
	@rm -f $(SERVER_OBJECTS)
	@rm -f $(CLIENT_OBJECTS)
	@rm -rf $(OBJS_DIR_SER)
	@rm -rf $(OBJS_DIR_CLI)
	@make clean -j 8 -C $(LIBFT_DIR)
	@echo "Delete objs"

re: fclean all
