/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 04:31:32 by sakitaha          #+#    #+#             */
/*   Updated: 2023/11/17 00:50:53 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

volatile sig_atomic_t	g_signal_pid_state;

static void	client_signal_action(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	if (g_signal_pid_state != info->si_pid)
		return ;
	if (sig == SIGUSR1)
		g_signal_pid_state = ACK_SERVER_FAIL;
	else if (sig == SIGUSR2)
		g_signal_pid_state = ACK_RECEIVED;
}

static bool	is_arg_numeric(const char *str)
{
	if (*str == '\0')
		return (false);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

static void	init_client(void)
{
	g_signal_pid_state = IDLE;
}

static pid_t	get_server_pid(const char *str)
{
	pid_t	pid;

	if (!is_arg_numeric(str))
		exit_with_error(INVALID_PID);
	pid = ft_atoi(str);
	if (pid < 2)
		exit_with_error(INVALID_PID);
	if (kill(pid, 0) < 0)
		exit_with_error(INVALID_PID);
	return (pid);
}

int	main(int argc, char const *argv[])
{
	pid_t	pid;

	if (argc != 3)
		exit_with_error(INVALID_ARGS);
	pid = get_server_pid(argv[1]);
	init_client();
	init_sigaction(client_signal_action);
	transmit_message(pid, argv[2]);
	return (0);
}
