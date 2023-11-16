/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 03:56:21 by sakitaha          #+#    #+#             */
/*   Updated: 2023/11/16 23:09:48 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

volatile sig_atomic_t	g_signal_pid_state;

static void	server_signal_action(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	if (g_signal_pid_state == IDLE)
	{
		g_signal_pid_state = info->si_pid;
		return ;
	}
	if (g_signal_pid_state != info->si_pid)
		return ;
	if (sig == SIGUSR1)
		g_signal_pid_state = ZERO;
	else if (sig == SIGUSR2)
		g_signal_pid_state = ONE;
}

void	reset_server(void)
{
	g_signal_pid_state = IDLE;
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
	msg_state->invalid_signal_count = 0;
	msg_state->is_end_of_message = false;
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
	reset_server();
	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	init_sigaction(server_signal_action);
	while (1)
	{
		pause();
		receive_message(msg_state);
		handle_signal_overflow(msg_state);
	}
	return (0);
}
