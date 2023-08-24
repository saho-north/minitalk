/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 03:56:21 by sakitaha          #+#    #+#             */
/*   Updated: 2023/08/24 15:08:43 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

volatile t_signal_info	g_client_info;

static void	signal_action(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	if (g_client_info.signal_status != SIG_FOR_WAITING)
		return ;
	if (g_client_info.current_pid == 0)
		g_client_info.current_pid = info->si_pid;
	else if (info->si_pid != g_client_info.current_pid)
		return ;
	if (sig == SIGUSR1)
		g_client_info.signal_status = SIG_FOR_ZERO_BIT;
	else if (sig == SIGUSR2)
		g_client_info.signal_status = SIG_FOR_ONE_BIT;
}

static void	init_server(void)
{
	g_client_info.current_pid = 0;
	g_client_info.signal_status = SIG_FOR_WAITING;
	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
}

int	main(void)
{
	init_server();
	init_sigaction(signal_action);
	while (1)
	{
		usleep(SLEEP_DURATION);
		handle_bit();
	}
	return (0);
}
