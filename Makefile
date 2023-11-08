NAME            = minitalk
CLIENT          = client
SERVER          = server
CC              = cc
CFLAGS          = -Wall -Wextra -Werror
LIBRARY         = -L$(LIBFT_DIR) -lft
INCLUDES        = -I$(HDR_DIR) -I$(LIBFT_DIR)

LIBFT           = $(LIBFT_DIR)libft.a
LIBFT_DIR       = ./libft/
LIBFT_HDR       = $(LIBFT_DIR)libft.h

HDR_LIST        = minitalk.h server.h client.h
HDR_DIR         = ./includes/
HDR             = $(addprefix $(HDR_DIR), $(HDR_LIST))

SRCS_COMMON     = exit_with_error.c init_sigaction.c
SRCS_CLIENT     = $(CLIENT).c transmit_message.c
SRCS_SERVER     = $(SERVER).c receive_message.c process_char.c server_utils.c

SRCS_COMMON_DIR = ./srcs/common/
SRCS_CLIENT_DIR = ./srcs/client/
SRCS_SERVER_DIR = ./srcs/server/

OBJS_COMMON     = $(addprefix $(SRCS_COMMON_DIR), $(SRCS_COMMON:.c=.o))
OBJS_CLIENT     = $(addprefix $(SRCS_CLIENT_DIR), $(SRCS_CLIENT:.c=.o))
OBJS_SERVER     = $(addprefix $(SRCS_SERVER_DIR), $(SRCS_SERVER:.c=.o))

$(NAME): $(CLIENT) $(SERVER)

$(CLIENT): $(OBJS_CLIENT) $(OBJS_COMMON) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBRARY)

$(SERVER): $(OBJS_SERVER) $(OBJS_COMMON) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBRARY)

$(LIBFT):
	make -C $(LIBFT_DIR)

all: $(NAME)

bonus: all

%.o: %.c $(HDR) $(LIBFT_HDR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS_CLIENT) $(OBJS_SERVER) $(OBJS_COMMON)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(CLIENT) $(SERVER)
	make -C $(LIBFT_DIR) fclean

re: fclean all

test: pre_test test_cases check_leaks kill_server
	rm -f .server_pid

pre_test: $(NAME)
	./$(SERVER) & echo $$! > .server_pid

test_cases:
	@echo "-----------------------------------------------------------"
	./$(CLIENT) `cat .server_pid` "Hello World"
	@echo ""
	@echo ""
	./$(CLIENT) `cat .server_pid` "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"
	@echo ""
	@echo ""
	./$(CLIENT) `cat .server_pid` "👨‍👩‍👧‍👦異体字！🐱🐈‍⬛猫の絵文字🐾42tokyo🗼"
	@echo ""
	@echo ""
	./$(CLIENT) `cat .server_pid` ""
	@echo ""
	@echo ""
	./$(CLIENT) `cat .server_pid` "a"
	@echo ""
	@echo ""
	./$(CLIENT) `cat .server_pid` "こんにちは ɧɛɫˡɵːŴởȑľð Χαῖρε добри́день سلام שלום Բարեւ"
	@echo ""
	@echo ""
	./$(CLIENT) `cat .server_pid` `python -c "print('.' * 10000)"`
	@echo ""
	@echo ""
	@echo "-----------------------------------------------------------"

check_leaks:
	sleep 1
	leaks `cat .server_pid`

kill_server:
	kill `cat .server_pid`
	kill -0 `cat .server_pid` && echo "Server still running" || echo "Server killed"

.PHONY: all clean fclean re test pre_test test_cases check_leaks kill_server
