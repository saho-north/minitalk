NAME	 = minitalk
CLIENT	 = client
SERVER	 = server
CC		 = cc
CFLAGS	 = -Wall -Wextra -Werror
LIBRARY    = -L$(LIBFT_DIR) -lft
INCLUDES   = -I$(HDR_DIR) -I$(LIBFT_DIR)

LIBFT	 = $(LIBFT_DIR)libft.a
LIBFT_DIR = ./libft/
LIBFT_HDR = $(LIBFT_DIR)libft.h

HDR_LIST = minitalk.h server.h client.h
HDR_DIR	 = ./
HDR		 = $(addprefix $(HDR_DIR), $(HDR_LIST))

SRCS_COMMON = exit_with_error.c init_sig.c
SRCS_CLIENT = $(CLIENT).c is_arg_numeric.c
SRCS_SERVER = $(SERVER).c

OBJS_COMMON = $(SRCS_COMMON:.c=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)
OBJS_SERVER = $(SRCS_SERVER:.c=.o)

$(NAME): $(CLIENT) $(SERVER)

$(CLIENT): $(OBJS_CLIENT) $(OBJS_COMMON) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBRARY)

$(SERVER): $(OBJS_SERVER) $(OBJS_COMMON) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBRARY)

$(LIBFT):
	make -C $(LIBFT_DIR)

all: $(NAME)

%.o: %.c $(HDR) $(LIBFT_HDR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS_CLIENT) $(OBJS_SERVER) $(OBJS_COMMON)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(CLIENT) $(SERVER)
	make -C $(LIBFT_DIR) fclean

re: fclean all

test: pre_test test0 test1 test2
	kill `cat .server_pid`
	kill -0 `cat .server_pid` 2>/dev/null && echo "Server still running" || echo "Server killed"

pre_test: $(NAME)
	./$(SERVER) & echo $$! > .server_pid

test0: $(NAME)
	sleep 1
	./$(CLIENT) `cat .server_pid` "Hello World"

test1: $(NAME)
	sleep 1
	./$(CLIENT) `cat .server_pid` "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"

test2: $(NAME)
	sleep 1
	./$(CLIENT) `cat .server_pid` `python -c "print('a' * 10000)"`

.PHONY: all clean fclean re test pre_test test0 test1 test2
