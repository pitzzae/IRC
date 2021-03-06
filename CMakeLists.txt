cmake_minimum_required(VERSION 3.7.2)
project(IRC)

set(CMAKE_CXX_STANDARD 11)

include_directories(includes)
include_directories(libft/includes)
set(HEADER_FILES_CLIENT libft/includes/libft.h includes/ft_irc_client.h)

set(HEADER_FILES_SERVER libft/includes/libft.h includes/ft_irc_server.h)


set(SOURCE_LIBFT libft/srcs/ft_atoi.c libft/srcs/ft_bzero.c
        libft/srcs/ft_isalnum.c libft/srcs/ft_isalpha.c
        libft/srcs/ft_isascii.c libft/srcs/ft_isdigit.c
        libft/srcs/ft_isprint.c libft/srcs/ft_memalloc.c
        libft/srcs/ft_memccpy.c libft/srcs/ft_memchr.c libft/srcs/ft_memcmp.c
        libft/srcs/ft_memcpy.c libft/srcs/ft_memmove.c libft/srcs/ft_memset.c
        libft/srcs/ft_strcat.c libft/srcs/ft_strchr.c libft/srcs/ft_strcmp.c
        libft/srcs/ft_strcpy.c libft/srcs/ft_strdup.c libft/srcs/ft_strlcat.c
        libft/srcs/ft_strlen.c libft/srcs/ft_strncat.c libft/srcs/ft_strncmp.c
        libft/srcs/ft_strncpy.c libft/srcs/ft_strnstr.c libft/srcs/ft_strrchr.c
        libft/srcs/ft_strstr.c libft/srcs/ft_tolower.c libft/srcs/ft_toupper.c
        libft/srcs/ft_memdel.c libft/srcs/ft_strnew.c libft/srcs/ft_strdel.c
        libft/srcs/ft_strclr.c libft/srcs/ft_striter.c libft/srcs/ft_striteri.c
        libft/srcs/ft_strmap.c libft/srcs/ft_strmapi.c libft/srcs/ft_strequ.c
        libft/srcs/ft_strnequ.c libft/srcs/ft_strsub.c libft/srcs/ft_strjoin.c
        libft/srcs/ft_strtrim.c libft/srcs/ft_strsplit.c libft/srcs/ft_itoa.c
        libft/srcs/ft_putchar.c libft/srcs/ft_putstr.c libft/srcs/ft_putendl.c
        libft/srcs/ft_putnbr.c libft/srcs/ft_putchar_fd.c
        libft/srcs/ft_putstr_fd.c libft/srcs/ft_putendl_fd.c
        libft/srcs/ft_putnbr_fd.c libft/srcs/ft_lstnew.c
        libft/srcs/ft_lstdelone.c libft/srcs/ft_lstdel.c libft/srcs/ft_lstadd.c
        libft/srcs/ft_lstaddend.c libft/srcs/ft_lstiter.c libft/srcs/ft_lstmap.c
        libft/srcs/ft_lstsplit.c libft/srcs/ft_lstprintstr.c
        libft/srcs/ft_lstprintnbr.c libft/srcs/ft_str_replace_chr.c
        libft/srcs/ft_lstlen.c libft/srcs/ft_lstring.c libft/srcs/ft_lstdup.c
        libft/srcs/ft_strfocur.c libft/srcs/get_next_line.c
        libft/srcs/ft_strjoin_free.c libft/srcs/ft_realloc.c
        libft/srcs/ft_tab_realloc.c libft/srcs/ft_strocur.c
        libft/srcs/ft_strlocur.c libft/srcs/ft_strcat_l.c libft/srcs/ft_bufcpy.c
        libft/srcs/ft_strisprint.c libft/srcs/ft_strswap.c
        libft/srcs/ft_date_time.c libft/srcs/ft_lst_env_new.c
        libft/srcs/ft_lst_to_env.c libft/srcs/ft_lst_get_env.c
        libft/srcs/ft_lst_edit_env.c libft/srcs/ft_lst_add_env.c
        libft/srcs/ft_lst_rm_env.c libft/srcs/ft_strsplit_len.c
        libft/srcs/ft_str_replace_str.c libft/srcs/ft_strsub_free.c
        libft/srcs/ft_myputchar.c libft/srcs/ft_lstaddend_free.c
        libft/srcs/ft_udel.c libft/srcs/ft_strocur_slash.c
        libft/srcs/ft_stradd_slash.c libft/srcs/ft_tabdup.c
        libft/srcs/ft_putbase.c libft/srcs/ft_puthex.c
        libft/srcs/ft_swapuint32.c libft/srcs/ft_swapuint8.c
        libft/srcs/ft_putstr_whsp.c libft/srcs/ft_pow.c libft/srcs/ft_putadd.c
        libft/srcs/ft_strnocur.c libft/srcs/ft_addchar_intstr.c libft/srcs/ft_delchar_intstr.c libft/srcs/ft_make_id.c)

add_library(ft STATIC ${SOURCE_LIBFT} ${HEADER_FILES})

set(APP_SERVER server)

set(APP_CLIENT client)

set(SOURCE_SERVER
        srcs/server/check_fd.c
        srcs/server/clean_fd.c
        srcs/server/client_read.c
        srcs/server/client_write.c
        srcs/server/do_select.c
        srcs/server/get_opt.c
        srcs/server/init_env.c
        srcs/server/init_fd.c
        srcs/server/main.c
        srcs/server/main_loop.c
        srcs/server/srv_accept.c
        srcs/server/srv_create.c
        srcs/server/x.c srcs/server/ft_parse_irc_cmd.c
        srcs/server/ft_irc_cmd_user.c srcs/server/ft_irc_cmd_nick.c
        srcs/server/ft_irc_cmd_who.c srcs/server/ft_irc_motd.c
        srcs/server/ft_irc_error.c srcs/server/ft_irc_print.c
        srcs/server/ft_irc_cmd_quit.c srcs/server/ft_send.c
        srcs/server/ft_irc_cmd_join.c srcs/server/ft_irc_cmd_leave.c
        srcs/server/ft_irc_get_chanel.c srcs/server/ft_irc_create_chanel.c
        srcs/server/ft_irc_cmd_chanel.c srcs/server/ft_irc_clear_empty_chanel.c
        srcs/server/ft_irc_chan_user.c srcs/server/ft_irc_leave_all_chan.c
        srcs/server/ft_irc_cmd_join_print.c srcs/server/ft_irc_cmd_leave_print.c
        srcs/server/ft_irc_cmd_msgpriv.c srcs/server/ft_irc_cmd_msgchanel.c
        srcs/server/ft_irc_parse_privmsg.c srcs/server/ft_irc_cmd_file.c srcs/server/client_buffer.c srcs/server/ft_irc_user_is_master_chanel.c srcs/server/ft_irc_cmd_quit_broadcast.c srcs/server/ft_irc_cmd_msg.c srcs/server/client_read_is_magic.c srcs/server/ft_irc_cmd_file_reply_broadcast.c srcs/server/ft_irc_cmd_file_reply_chanel.c srcs/server/ft_irc_cmd_file_reply_ack.c)

set(SOURCE_CLIENT
        srcs/client/check_fd.c
        srcs/client/clean_fd.c
        srcs/client/client_read.c
        srcs/client/client_write.c
        srcs/client/do_select.c
        srcs/client/get_opt.c
        srcs/client/init_env.c
        srcs/client/init_fd.c
        srcs/client/main.c
        srcs/client/main_loop.c
        srcs/client/client_create.c
        srcs/client/x.c srcs/client/ft_terminos.c srcs/client/ft_terms_read.c srcs/client/ft_terminos_move.c srcs/client/ft_client_prompt.c srcs/client/ft_history_cmd.c srcs/client/ft_parse_irc_cmd.c srcs/client/ft_irc_cmd_msg.c srcs/client/ft_irc_cmd_nick.c srcs/client/ft_irc_cmd_user.c srcs/client/ft_irc_cmd_who.c srcs/client/ft_irc_cmd_quit.c srcs/client/ft_irc_cmd_join.c srcs/client/ft_irc_cmd_leave.c srcs/client/ft_irc_cmd_file.c srcs/client/ft_irc_print.c srcs/client/ft_irc_cmd_help.c srcs/client/ft_send.c srcs/client/ft_irc_cmd_connect.c srcs/client/ft_irc_cmd_error_arg.c srcs/client/ft_irc_update_prompt.c srcs/client/ft_irc_parse_return.c srcs/client/ft_irc_parse_reply.c srcs/client/ft_irc_parse_reply_handle.c srcs/client/ft_irc_file_make_packet.c srcs/client/ft_irc_open_file.c srcs/client/ft_irc_send_files.c srcs/client/ft_irc_write_file.c srcs/client/ft_irc_accept_transfert.c srcs/client/ft_irc_create_file.c srcs/client/ft_irc_cat_infile.c srcs/client/ft_irc_close_file.c srcs/client/ft_irc_parse_is_file.c)

add_executable( ${APP_SERVER} ${HEADER_FILES_SERVER} ${SOURCE_SERVER} ${SOURCE_LIBFT} )
target_link_libraries( ${APP_SERVER} ft)

add_executable( ${APP_CLIENT} ${HEADER_FILES_CLIENT} ${SOURCE_CLIENT} ${SOURCE_LIBFT} )
target_link_libraries( ${APP_CLIENT} ft ncurses)