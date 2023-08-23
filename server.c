/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 03:56:21 by sakitaha          #+#    #+#             */
/*   Updated: 2023/08/24 07:08:38 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

volatile t_signal_data	g_client_status;

static void	signal_action(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	if (g_client_status.signal_status != SIG_FOR_WAITING)
	{
		return ;
	}
	if (g_client_status.current_pid == 0)
	{
		g_client_status.current_pid = info->si_pid;
	}
	else if (info->si_pid != g_client_status.current_pid)
	{
		return ;
	}
	if (sig == SIGUSR1)
	{
		g_client_status.signal_status = SIG_FOR_ZERO_BIT;
	}
	else if (sig == SIGUSR2)
	{
		g_client_status.signal_status = SIG_FOR_ONE_BIT;
	}
}

static void	initialize_server(void)
{
	g_client_status.current_pid = 0;
	g_client_status.signal_status = SIG_FOR_WAITING;
	init_sig(signal_action);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
}

static void	process_bit(char *current_char, size_t *bits_count)
{
	if (g_client_status.signal_status == SIG_FOR_ONE_BIT)
	{
		*current_char |= 1 << (7 - *bits_count);
	}
	(*bits_count)++;
}

static void	confirm_char(char *current_char, size_t *bits_count)
{
	if (*bits_count == 8)
	{
		if (*current_char != 0x02 && *current_char != 0x03)
			write(1, current_char, 1);
		else if (*current_char == 0x03)
		{
			write(1, "\n", 1);
			g_client_status.current_pid = 0;
		}
		*current_char = 0;
		*bits_count = 0;
	}
}

static void	handle_bit(void)
{
	static char		current_char;
	static size_t	bits_count;
	pid_t			client_pid;

	client_pid = g_client_status.current_pid;
	if (client_pid == 0)
	{
		current_char = 0;
		bits_count = 0;
		return ;
	}
	if (g_client_status.signal_status == SIG_FOR_WAITING)
	{
		return ;
	}
	process_bit(&current_char, &bits_count);
	confirm_char(&current_char, &bits_count);
	g_client_status.signal_status = SIG_FOR_WAITING;
	if (kill(client_pid, SIGUSR2) < 0)
		exit_with_error(KILL_FAIL);
}

int	main(void)
{
	initialize_server();
	while (1)
	{
		usleep(SLEEP_DURATION);
		handle_bit();
	}
	return (0);
}
