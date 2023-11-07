/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 03:56:21 by sakitaha          #+#    #+#             */
/*   Updated: 2023/11/07 23:11:01 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

volatile t_signal_info	g_server_info;

void	reset_server_info(void)
{
	g_server_info.current_pid = 0;
	g_server_info.signal_status = WAITING_FOR_SIGNAL;
}

static void	server_signal_action(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	if (g_server_info.current_pid == 0)
		g_server_info.current_pid = info->si_pid;
	else if (g_server_info.current_pid != info->si_pid)
		return ;
	if (g_server_info.signal_status != WAITING_FOR_SIGNAL)
		return ;
	if (sig == SIGUSR1)
		g_server_info.signal_status = ZERO_BIT;
	else if (sig == SIGUSR2)
		g_server_info.signal_status = ONE_BIT;
}

void	reset_msg_state(t_msg_state *msg_state)
{
	free(msg_state->buf);
	msg_state->buf = NULL;
	msg_state->buf = (char *)malloc(sizeof(char) * INITIAL_BUF_SIZE);
	if (!msg_state->buf)
	{
		free(msg_state);
		exit_with_error(MALLOC_FAIL);
	}
	msg_state->buf_index = 0;
	msg_state->buf_size = INITIAL_BUF_SIZE;
	msg_state->current_char = 0;
	msg_state->bits_count = 0;
	msg_state->sender_pid = 0;
	msg_state->call_count = 0;
	msg_state->is_first_signal = true;
	msg_state->is_last_signal = false;
}

static t_msg_state	*init_msg_state(void)
{
	t_msg_state	*new_state;

	new_state = (t_msg_state *)malloc(sizeof(t_msg_state));
	if (!new_state)
		exit_with_error(MALLOC_FAIL);
	new_state->buf = NULL;
	reset_msg_state(new_state);
	return (new_state);
}

int	main(void)
{
	t_msg_state	*msg_state;

	msg_state = init_msg_state();
	reset_server_info();
	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	init_sigaction(server_signal_action);
	while (1)
	{
		pause();
		receive_message(msg_state);
		check_call_limit(msg_state);
	}
	return (0);
}
