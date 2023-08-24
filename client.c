/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 04:31:32 by sakitaha          #+#    #+#             */
/*   Updated: 2023/08/24 21:05:14 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

volatile t_signal_info			g_client_info;

static void	signal_action(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	if (g_client_info.signal_status != ACK_WAITING)
	{
		return ;
	}
	if (info->si_pid != g_client_info.current_pid)
	{
		return ;
	}
	if (sig == SIGUSR1)
	{
		g_client_info.signal_status = ACK_SERVER_BUSY;
	}
	else if (sig == SIGUSR2)
	{
		g_client_info.signal_status = ACK_RECEIVED;
	}
}

static t_signal_acknowledgement	check_server_ack(void)
{
	size_t	sleep_count;

	sleep_count = 0;
	while (1)
	{
		usleep(SLEEP_DURATION);
		if (g_client_info.signal_status != ACK_WAITING)
		{
			break ;
		}
		sleep_count++;
		if (sleep_count * SLEEP_DURATION > TIMEOUT_LIMIT)
		{
			g_client_info.signal_status = ACK_TIME_OUT;
			break ;
		}
	}
	return (g_client_info.signal_status);
}

static void	transmit_bit(pid_t pid, char bit)
{
	if (bit)
	{
		if (kill(pid, SIGUSR2) < 0)
			exit_with_error(KILL_FAIL);
	}
	else
	{
		if (kill(pid, SIGUSR1) < 0)
			exit_with_error(KILL_FAIL);
	}
}

static void	transmit_char(pid_t pid, char c)
{
	size_t	bit_index;
	size_t	retries;

	bit_index = 8;
	retries = 0;
	while (bit_index-- > 0)
	{
		g_client_info.signal_status = ACK_WAITING;
		transmit_bit(pid, (c >> bit_index) & 1);
		if (check_server_ack() != ACK_RECEIVED)
		{
			retries++;
			if (retries > MAX_RETRIES)
				exit_with_error(TIMEOUT);
			bit_index++;
		}
		else
			retries = 0;
	}
}

static void	transmit_message(pid_t pid, const char *str)
{
	transmit_char(pid, 0x02);
	while (*str)
	{
		transmit_char(pid, *str);
		usleep(SLEEP_DURATION);
		str++;
	}
	transmit_char(pid, 0x03);
}

static void	init_client(int argc, char const *argv[])
{
	g_client_info.current_pid = 0;
	g_client_info.signal_status = ACK_WAITING;
	if (argc != 3 || !is_arg_numeric(argv[1]))
	{
		exit_with_error(INVALID_ARGS);
	}
	g_client_info.current_pid = ft_atoi(argv[1]);
	if (g_client_info.current_pid < 1)
	{
		exit_with_error(INVALID_PID);
	}
	if (kill(g_client_info.current_pid, 0) < 0)
	{
		exit_with_error(INVALID_PID);
	}
}

int	main(int argc, char const *argv[])
{
	init_client(argc, argv);
	init_sigaction(signal_action);
	transmit_message(g_client_info.current_pid, argv[2]);
	return (0);
}
