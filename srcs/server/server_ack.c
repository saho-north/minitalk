/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_ack.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:49:32 by sakitaha          #+#    #+#             */
/*   Updated: 2023/11/17 14:56:50 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	notify_failure(t_msg_state *msg_state)
{
	if (msg_state->sender_pid == 0)
		return ;
	if (kill(msg_state->sender_pid, SIGUSR1) < 0)
		free_and_exit(msg_state, KILL_FAIL);
}

void	send_ack(t_msg_state *msg_state)
{
	if (msg_state->sender_pid == 0)
		return ;
	if (kill(msg_state->sender_pid, SIGUSR2) < 0)
		free_and_exit(msg_state, KILL_FAIL);
}
