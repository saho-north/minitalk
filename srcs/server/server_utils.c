/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:10:07 by sakitaha          #+#    #+#             */
/*   Updated: 2023/09/01 05:43:01 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

bool	has_no_current_client(void)
{
	return (g_server_info.current_pid == 0);
}

bool	is_waiting_signal(void)
{
	return (g_server_info.signal_status == WAITING_FOR_SIGNAL);
}

void	check_call_limit(t_msg_state *msg_state)
{
	if (msg_state->call_count > CALL_LIMIT)
	{
		ft_putstr_fd("Warning: Call limit reached. Resetting state.\n", 1);
		reset_server_info();
		reset_msg_state(msg_state);
	}
}

void	free_and_exit(t_msg_state *msg_state, t_error_type error)
{
	free(msg_state->buf);
	free(msg_state);
	exit_with_error(error);
}
