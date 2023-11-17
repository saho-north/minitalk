/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transmit_message.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 22:20:42 by sakitaha          #+#    #+#             */
/*   Updated: 2023/11/17 16:07:19 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void	print_result(size_t ack_count)
{
	ft_putstr_fd("\nTotal ACKs received: ", 1);
	ft_putnbr_fd(ack_count, 1);
	ft_putstr_fd("\nTotal bytes transmitted: ", 1);
	ft_putnbr_fd((ack_count - 9) / 8, 1);
	ft_putchar_fd('\n', 1);
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

static void	transmit_byte(pid_t pid, char c, size_t *ack_count)
{
	int				bit_index;
	size_t			attempt_count;
	sig_atomic_t	ack_status;

	bit_index = 7;
	attempt_count = 0;
	while (bit_index >= 0)
	{
		g_signal_pid_state = pid;
		transmit_bit(pid, (c >> bit_index) & 1);
		attempt_count++;
		ack_status = get_ack_status();
		if (ack_status == ACK_RECEIVED)
		{
			bit_index--;
			attempt_count = 0;
			(*ack_count)++;
		}
		else if (ack_status == ACK_SERVER_FAIL)
			exit_with_error(SERVER_FAIL);
		else if (attempt_count > MAX_ATTEMPTS)
			exit_with_error(TIMEOUT);
	}
}

static void	send_initial_signal(pid_t pid, size_t *ack_count)
{
	size_t			attempt_count;
	sig_atomic_t	ack_status;

	attempt_count = 0;
	while (true)
	{
		g_signal_pid_state = pid;
		if (kill(pid, SIGUSR1) < 0)
			exit_with_error(KILL_FAIL);
		attempt_count++;
		ack_status = get_ack_status();
		if (ack_status == ACK_RECEIVED)
		{
			(*ack_count)++;
			break ;
		}
		else if (ack_status == ACK_SERVER_FAIL)
			exit_with_error(SERVER_FAIL);
		else if (attempt_count > MAX_ATTEMPTS)
			exit_with_error(TIMEOUT);
	}
}

void	transmit_message(pid_t pid, const char *str)
{
	size_t	ack_count;

	ack_count = 0;
	send_initial_signal(pid, &ack_count);
	while (*str)
	{
		transmit_byte(pid, *str, &ack_count);
		str++;
	}
	transmit_byte(pid, '\0', &ack_count);
	print_result(ack_count);
}
