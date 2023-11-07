/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 04:31:32 by sakitaha          #+#    #+#             */
/*   Updated: 2023/11/07 23:59:40 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

volatile t_signal_info	g_client_info;

static void	client_signal_action(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	if (info->si_pid != g_client_info.current_pid)
		return ;
	if (g_client_info.signal_status != ACK_WAITING)
		return ;
	if (sig == SIGUSR1)
		g_client_info.signal_status = ACK_SERVER_FAIL;
	else if (sig == SIGUSR2)
		g_client_info.signal_status = ACK_RECEIVED;
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

static void	is_valid_pid(const char *str)
{
	if (!is_arg_numeric(str))
		exit_with_error(INVALID_PID);
	g_client_info.current_pid = ft_atoi(str);
	if (g_client_info.current_pid < 1)
		exit_with_error(INVALID_PID);
	if (kill(g_client_info.current_pid, 0) < 0)
		exit_with_error(INVALID_PID);
}

static void	init_client(void)
{
	g_client_info.current_pid = 0;
	g_client_info.signal_status = ACK_WAITING;
}

int	main(int argc, char const *argv[])
{
	if (argc != 3)
		exit_with_error(INVALID_ARGS);
	init_client();
	is_valid_pid(argv[1]);
	init_sigaction(client_signal_action);
	transmit_message(g_client_info.current_pid, argv[2]);
	return (0);
}
