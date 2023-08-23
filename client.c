/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 04:31:32 by sakitaha          #+#    #+#             */
/*   Updated: 2023/08/24 04:31:54 by sakitaha         ###   ########.fr       */
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

static volatile t_signal_data	g_signal_data;

static void	signal_action(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	if (g_signal_data.signal_status != ACK_WAITING)
	{
		return ;
	}
	if (info->si_pid != g_signal_data.current_pid)
	{
		return ;
	}
	if (sig == SIGUSR1)
	{
		g_signal_data.signal_status = ACK_SERVER_BUSY;
	}
	else if (sig == SIGUSR2)
	{
		g_signal_data.signal_status = ACK_RECEIVED;
	}
}

static t_signal_acknowledgement	is_signal_acknowledged(void)
{
	size_t	sleep_count;

	sleep_count = 0;
	while (1)
	{
		usleep(SLEEP_DURATION);
		if (g_signal_data.signal_status != ACK_WAITING)
			break ;
		sleep_count++;
		if (sleep_count * SLEEP_DURATION > TIMEOUT_LIMIT)
		{
			g_signal_data.signal_status = ACK_TIME_OUT;
			break ;
		}
	}
	return (g_signal_data.signal_status);
}

static void	transmit_char(pid_t pid, char c)
{
	size_t	bit_index;
	size_t	counter_for_retry;

	bit_index = 8;
	counter_for_retry = 0;
	while (bit_index-- > 0)
	{
		g_signal_data.signal_status = ACK_WAITING;
		if ((c >> bit_index) & 1)
		{
			if (kill(pid, SIGUSR2) < 0)
				exit_with_error(KILL_FAIL);
		}
		else
		{
			if (kill(pid, SIGUSR1) < 0)
				exit_with_error(KILL_FAIL);
		}
		if (is_signal_acknowledged() != ACK_RECEIVED)
		{
			counter_for_retry++;
			if (counter_for_retry > 10)
				exit_with_error(TIMEOUT);
			bit_index++;
		}
	}
}

static void	send_message(pid_t pid, const char *str)
{
	//ここでstrの長さを送る実装を後程行う
	transmit_char(pid, 0x02);
	while (*str)
	{
		transmit_char(pid, *str);
		usleep(SLEEP_DURATION);
		str++;
	}
	transmit_char(pid, 0x03);
}

int	main(int argc, char const *argv[])
{
	g_signal_data.current_pid = 0;
	g_signal_data.signal_status = ACK_WAITING;
	if (argc != 3 || !is_arg_numeric(argv[1]))
	{
		exit_with_error(INVALID_ARGS);
	}
	g_signal_data.current_pid = ft_atoi(argv[1]);
	if (g_signal_data.current_pid < 1)
	{
		exit_with_error(INVALID_PID);
	}
	if (kill(g_signal_data.current_pid, 0) < 0)
	{
		exit_with_error(INVALID_PID);
	}
	init_sigaction(signal_action);
	send_message(g_signal_data.current_pid, argv[2]);
	return (0);
}
