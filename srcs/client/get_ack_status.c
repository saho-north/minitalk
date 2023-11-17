/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ack_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:41:12 by sakitaha          #+#    #+#             */
/*   Updated: 2023/11/17 15:43:21 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static bool	has_ack(void)
{
	return (g_signal_pid_state == ACK_RECEIVED
		|| g_signal_pid_state == ACK_SERVER_FAIL);
}

sig_atomic_t	get_ack_status(void)
{
	size_t	sleep_count;

	sleep_count = 0;
	while (!has_ack())
	{
		usleep(SLEEP_DURATION);
		sleep_count++;
		if (sleep_count * SLEEP_DURATION > TIMEOUT_LIMIT)
			break ;
	}
	return (g_signal_pid_state);
}
