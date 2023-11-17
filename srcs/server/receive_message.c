/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_message.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 05:08:31 by sakitaha          #+#    #+#             */
/*   Updated: 2023/11/17 14:56:13 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	ready_for_next_signal(t_msg_state *msg_state)
{
	g_signal_pid_state = msg_state->sender_pid;
	msg_state->invalid_signal_count = 0;
}

static void	process_received_bit(t_msg_state *msg_state)
{
	if (g_signal_pid_state == ONE)
		msg_state->current_char |= 1 << (7 - msg_state->bits_count);
	msg_state->bits_count++;
	if (msg_state->bits_count == CHAR_BIT)
		process_char(msg_state);
}

static bool	is_valid_signal(t_msg_state *msg_state)
{
	if (has_signal() && msg_state->sender_pid != 0)
		return (true);
	msg_state->invalid_signal_count++;
	return (false);
}

static bool	is_new_client(t_msg_state *msg_state)
{
	if (has_pid() && msg_state->sender_pid == 0)
	{
		msg_state->sender_pid = g_signal_pid_state;
		send_ack(msg_state);
		return (true);
	}
	return (false);
}

void	receive_message(t_msg_state *msg_state)
{
	if (is_new_client(msg_state))
		return ;
	if (!is_valid_signal(msg_state))
		return ;
	process_received_bit(msg_state);
	ready_for_next_signal(msg_state);
	send_ack(msg_state);
	check_end_of_message(msg_state);
}
