/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:10:07 by sakitaha          #+#    #+#             */
/*   Updated: 2023/11/16 23:09:48 by sakitaha         ###   ########.fr       */
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

bool	is_server_idle(void)
{
	return (g_signal_pid_state == IDLE);
}

bool	has_signal(void)
{
	return (g_signal_pid_state == ZERO || g_signal_pid_state == ONE);
}

bool	has_pid(void)
{
	return (g_signal_pid_state > 1);
}

void	handle_signal_overflow(t_msg_state *msg_state)
{
	if (msg_state->invalid_signal_count > MAX_INVALID_SIGNALS)
	{
		ft_putstr_fd("Warning: Call limit reached. Resetting state.\n", 1);
		reset_server();
		reset_msg_state(msg_state);
	}
}

void	free_and_exit(t_msg_state *msg_state, t_error_type error)
{
	free(msg_state->buf);
	free(msg_state);
	exit_with_error(error);
}
