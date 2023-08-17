/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 04:31:32 by sakitaha          #+#    #+#             */
/*   Updated: 2023/08/18 02:52:29 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>

volatile sig_atomic_t	g_signal_status;

static void	signal_handler(int sig)
{
	if (sig == SIGUSR1)
	{
		g_signal_status = 0;
	}
	else if (sig == SIGUSR2)
	{
		g_signal_status = 1;
	}
}

static bool	is_responce_valid(void)
{
	size_t	timeout_counter;

	timeout_counter = 0;
	while (g_signal_status == -1)
	{
		if (timeout_counter * SLEEP_DURATION > TIMEOUT_LIMIT)
		{
			ft_putendl_fd("Error: Timeout", 2);
			exit(1);
		}
		usleep(SLEEP_DURATION);
		timeout_counter++;
	}
	if (g_signal_status == 0)
	{
		ft_putendl_fd("Error: Failed to send signal", 2);
		exit(1);
	}
	return (true);
}

static void	transmit_char(pid_t pid, char c)
{
	size_t	bit_index;

	g_signal_status = 1;
	bit_index = 8;
	while (bit_index-- > 0 && is_responce_valid())
	{
		g_signal_status = -1;
		if ((c >> bit_index) & 1)
		{
			if (kill(pid, SIGUSR2) < 0)
			{
				ft_putendl_fd("Error: Failed to send signal", 2);
				exit(1);
			}
		}
		else
		{
			if (kill(pid, SIGUSR1) < 0)
			{
				ft_putendl_fd("Error: Failed to send signal", 2);
				exit(1);
			}
		}
	}
}

static void	send_message(pid_t pid, const char *str)
{
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
	struct sigaction	sa;
	pid_t				pid;

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
	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	send_message(pid, argv[2]);
	return (0);
}
