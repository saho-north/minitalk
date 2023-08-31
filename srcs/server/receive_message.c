/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_message.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 05:08:31 by sakitaha          #+#    #+#             */
/*   Updated: 2023/09/01 03:57:51 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	send_ack(t_msg_state *msg_state)
{
	if (kill(msg_state->sender_pid, SIGUSR2) < 0)
		free_and_exit(msg_state, KILL_FAIL);
}

static void	process_received_bit(t_msg_state *msg_state)
{
	if (g_server_info.signal_status == ONE_BIT)
		msg_state->current_char |= 1 << (7 - msg_state->bits_count);
	msg_state->bits_count++;
	if (msg_state->bits_count == 8)
	{
		put_char_into_buf(msg_state);
		msg_state->current_char = 0;
		msg_state->bits_count = 0;
	}
}

void	receive_message(t_msg_state *msg_state)
{
	msg_state->call_count++;
	if (has_no_current_client() || is_waiting_signal())
		return ;
	if (msg_state->sender_pid == 0)
		msg_state->sender_pid = g_server_info.current_pid;
	process_received_bit(msg_state);
	g_server_info.signal_status = WAITING_FOR_SIGNAL;
	msg_state->call_count = 0;
	send_ack(msg_state);
	if (msg_state->is_last_signal)
	{
		reset_server_info();
		reset_msg_state(msg_state);
	}
}
