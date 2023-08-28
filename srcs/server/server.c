/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 03:56:21 by sakitaha          #+#    #+#             */
/*   Updated: 2023/08/28 20:11:30 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

volatile sig_atomic_t	g_server_signal_status;

static void	handle_client_signal(int sig, siginfo_t *info, void *ucontext)
{
	static volatile sig_atomic_t	client_pid;

	(void)ucontext;
	if (g_server_signal_status == SIG_READY_FOR_NEW_CLIENT)
	{
		client_pid = info->si_pid;
		g_server_signal_status = SIG_FOR_WAITING;
	}
	else if (info->si_pid != client_pid)
		return ;
	else if (g_server_signal_status != SIG_FOR_WAITING)
		return ;
	if (sig == SIGUSR1)
		g_server_signal_status = SIG_FOR_ZERO_BIT;
	else if (sig == SIGUSR2)
		g_server_signal_status = SIG_FOR_ONE_BIT;
	if (kill(client_pid, SIGUSR2) < 0)
		g_server_signal_status = SIG_KILL_ERROR;
}

static void	init_server(void)
{
	g_server_signal_status = SIG_READY_FOR_NEW_CLIENT;
	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
}

int	main(void)
{
	init_server();
	init_sigaction(handle_client_signal);
	while (1)
	{
		pause();
		// TODO: add error handling for kill error case
		// TODO: Implement timeout handling
		// Timeout occurs when g_server_signal_status is SIG_FOR_WAITING
		// for a certain amount of time (no signal from the client).
		// Handle the timeout condition here.
		handle_bit();
	}
	return (0);
}
