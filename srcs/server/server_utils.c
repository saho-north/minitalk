/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:10:07 by sakitaha          #+#    #+#             */
/*   Updated: 2023/11/17 16:21:50 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	check_end_of_message(t_msg_state *msg_state)
{
	if (msg_state->is_end_of_message)
	{
		reset_server();
		reset_msg_state(msg_state);
	}
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
		ft_putstr_fd("Warning: Call limit reached. Resetting state.\n", 2);
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
