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
SRCS_CLIENT     = $(CLIENT).c transmit_message.c get_ack_status.c
SRCS_SERVER     = $(SERVER).c receive_message.c process_char.c server_utils.c server_ack.c

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
	@echo ""
	@echo "<--- Test Cases --->"
	@echo "1. ASCII characters"
	./$(CLIENT) `cat .server_pid` "Hello World"
	@echo ""
	@echo "2. Extended ASCII characters"
	./$(CLIENT) `cat .server_pid` "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"
	@echo ""
	@echo "3. Non-ASCII characters (Emojis, Japanese, etc.)"
	./$(CLIENT) `cat .server_pid` "👨‍👩‍👧‍👦🐈😺絵文字🐈‍⬛🐾🦆"
	@echo ""
	@echo "4. Combination of ASCII and Non-ASCII characters"
	./$(CLIENT) `cat .server_pid` "🗼42tokyo🗼"
	@echo ""
	@echo "5. Empty string"
	./$(CLIENT) `cat .server_pid` ""
	@echo ""
	@echo "6. Single character"
	./$(CLIENT) `cat .server_pid` "a"
	@echo ""
	@echo "7. Multilingual string (various non-ASCII languages)"
	./$(CLIENT) `cat .server_pid` "プログラミング (Japanese) 编程 (Chinese) программирование (Russian) البرمجة (Arabic) 프로그래밍 (Korean) प्रोग्रामिंग (Hindi) Προγραμματισμός (Greek) תכנות (Hebrew) การเขียนโปรแกรม (Thai) പ്രോഗ്രാമിംഗ് (Malayalam)"
	@echo ""
	@echo "8. Very long string"
	./$(CLIENT) `cat .server_pid` `python -c "print('.' * 10000)"`
	@echo ""
	@echo "9. Control characters"
	./$(CLIENT) `cat .server_pid` `python -c "print('\x02\x03\x04')"`
	@echo ""
	@echo "-----------------------------------------------------------"

check_leaks:
	sleep 1
	leaks `cat .server_pid`

kill_server:
	kill `cat .server_pid`
	kill -0 `cat .server_pid` && echo "Server still running" || echo "Server killed"

.PHONY: all clean fclean re test pre_test test_cases check_leaks kill_server
