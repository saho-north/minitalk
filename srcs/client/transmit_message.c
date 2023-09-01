/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transmit_message.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 22:20:42 by sakitaha          #+#    #+#             */
/*   Updated: 2023/09/01 15:38:29 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static t_signal_acknowledgement	is_ack_received(void)
{
	size_t	sleep_count;

	sleep_count = 0;
	while (g_client_info.signal_status == ACK_WAITING)
	{
		usleep(SLEEP_DURATION);
		sleep_count++;
		if (sleep_count * SLEEP_DURATION > TIMEOUT_LIMIT)
			break ;
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

static void	transmit_byte(pid_t pid, char c)
{
	int		bit_index;
	size_t	retry_count;

	bit_index = 7;
	retry_count = 0;
	while (bit_index >= 0)
	{
		g_client_info.signal_status = ACK_WAITING;
		transmit_bit(pid, (c >> bit_index) & 1);
		if (is_ack_received() == ACK_RECEIVED)
		{
			bit_index--;
			retry_count = 0;
		}
		else
		{
			retry_count++;
			if (retry_count > MAX_RETRIES)
				exit_with_error(TIMEOUT);
		}
	}
}

void	transmit_message(pid_t pid, const char *str)
{
	transmit_byte(pid, START_OF_TXT);
	while (*str)
	{
		transmit_byte(pid, *str);
		str++;
	}
	transmit_byte(pid, END_OF_TXT);
}
