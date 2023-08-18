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

HDR_LIST = minitalk.h
HDR_DIR	 = ./
HDR		 = $(addprefix $(HDR_DIR), $(HDR_LIST))

SRCS_COMMON = minitalk_utils.c write_bi_char.c
SRCS_CLIENT = $(CLIENT).c is_valid_pid.c
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

testserver: $(SERVER) clean
	./$(SERVER)

testclient: $(CLIENT) clean
	./$(CLIENT) 1234 "Hello World"

test: $(NAME)
	./$(SERVER) & echo $$! > .server_pid
	sleep 1
	./$(CLIENT) `cat .server_pid` "Hello World"
	kill `cat .server_pid`
	kill -0 `cat .server_pid` 2>/dev/null && echo "Server still running" || echo "Server killed"

.PHONY: all clean fclean re test testserver testclient
