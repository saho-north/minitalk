/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_message.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 05:08:31 by sakitaha          #+#    #+#             */
/*   Updated: 2023/11/09 15:11:09 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	send_ack(t_msg_state *msg_state)
{
	if (msg_state->sender_pid == 0)
		return ;
	if (kill(msg_state->sender_pid, SIGUSR2) < 0)
		free_and_exit(msg_state, KILL_FAIL);
}

static void	ready_for_next_signal(t_msg_state *msg_state)
{
	g_server_info.signal_status = WAITING_FOR_SIGNAL;
	msg_state->invalid_signal_count = 0;
}

static void	check_end_of_message(t_msg_state *msg_state)
{
	if (msg_state->is_end_of_message)
	{
		reset_server_info();
		reset_msg_state(msg_state);
	}
}

static void	process_received_bit(t_msg_state *msg_state)
{
	if (g_server_info.signal_status == ONE_BIT)
		msg_state->current_char |= 1 << (7 - msg_state->bits_count);
	msg_state->bits_count++;
	if (msg_state->bits_count == CHAR_BIT)
		process_char(msg_state);
}

void	receive_message(t_msg_state *msg_state)
{
	if (has_no_current_client() || is_waiting_signal())
	{
		msg_state->invalid_signal_count++;
		return ;
	}
	if (msg_state->sender_pid == 0)
		msg_state->sender_pid = g_server_info.current_pid;
	process_received_bit(msg_state);
	ready_for_next_signal(msg_state);
	send_ack(msg_state);
	check_end_of_message(msg_state);
}
