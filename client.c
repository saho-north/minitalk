/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 04:31:32 by sakitaha          #+#    #+#             */
/*   Updated: 2023/08/19 00:11:04 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
- ACKは大体実装できたはずである
- ACKを送る前に、strの長さを送る実装を後で行う
- mallocの成否を受け取る実装が必要
- 送信する文字列の長さが、intの範囲を超える場合の実装が必要
- Unicode characters supportの実装が必要 <- やり方がわからないのでリサーチする
- 1 second for displaying 100 characters is way too much! <- これは、sleepの時間を短くすることで解決できるはず
- timeoutの時に、一定回数は再送を試みる実装が必要（serverのmalloc中には確認応答しないため）

 */

static volatile sig_atomic_t	g_signal_status;

// static void	signal_handler(int sig)
// {
// 	if (sig == SIGUSR1)
// 	{
// 		g_signal_status = 0;
// 	}
// 	else if (sig == SIGUSR2)
// 	{
// 		g_signal_status = 1;
// 	}
// }

// static t_signal_acknowledgement	is_responce_valid(void)
// {
// 	size_t	timeout_counter;

// 	timeout_counter = 0;
// 	while (g_signal_status == -1)
// 	{
// 		if (timeout_counter * SLEEP_DURATION > TIMEOUT_LIMIT)
// 		{
// 			ft_putendl_fd("Error: Timeout", 2);
// 			exit(1);
// 		}
// 		usleep(SLEEP_DURATION);
// 		timeout_counter++;
// 	}
// 	if (g_signal_status == 0)
// 		return (SERVER_BUSY);
// 	return (SIGNAL_RECEIVED);
// }

static void	transmit_char(pid_t pid, char c)
{
	size_t	bit_index;

	g_signal_status = 1;
	bit_index = 8;
	while (bit_index-- > 0)
	{
		g_signal_status = -1;
		if ((c >> bit_index) & 1)
		{
			ft_putchar_fd('1', 1);
			if (kill(pid, SIGUSR2) < 0)
			{
				ft_putendl_fd("Error: Failed to send signal", 2);
				exit(1);
			}
		}
		else
		{
			ft_putchar_fd('0', 1);
			if (kill(pid, SIGUSR1) < 0)
			{
				ft_putendl_fd("Error: Failed to send signal", 2);
				exit(1);
			}
		}
		// if (is_responce_valid() == SERVER_BUSY)
		// {
		// 	usleep(SLEEP_DURATION);
		// 	continue ;
		// }
	}
	ft_putchar_fd('\n', 1);
}

static void	send_message(pid_t pid, const char *str)
{
	//最初にここでstrの長さを送る実装を後程行う
	transmit_char(pid, 0x02);
	while (*str)
	{
		transmit_char(pid, *str);
		str++;
	}
	transmit_char(pid, 0x03);
}

int	main(int argc, char const *argv[])
{
	pid_t	pid;

	//struct sigaction	sa;
	if (argc != 3 || !is_valid_pid(argv[1]))
	{
		ft_putendl_fd("Error: Invalid arguments", 2);
		ft_putendl_fd("Usage: ./client [server PID] [message]", 2);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	if (kill(pid, 0) < 0)
	{
		ft_putendl_fd("Error: Invalid PID", 2);
		return (1);
	}
	// sa.sa_handler = signal_handler;
	// sigemptyset(&sa.sa_mask);
	// sa.sa_flags = 0;
	// if (sigaction(SIGUSR1, &sa, NULL) < 0 || sigaction(SIGUSR2, &sa,
	//		NULL) < 0)
	// {
	// 	ft_putendl_fd("Error: sigaction failed", 2);
	// 	return (1);
	// }
	//send_messageの前に、strの長さを送る実装を後で行う
	send_message(pid, argv[2]);
	return (0);
}
