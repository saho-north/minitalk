/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sigaction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 01:27:45 by sakitaha          #+#    #+#             */
/*   Updated: 2023/11/06 17:12:26 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	init_sigaction(void (*signal_action)(int, siginfo_t *, void *))
{
	struct sigaction	sa_usr1;
	struct sigaction	sa_usr2;

	ft_bzero(&sa_usr1, sizeof(sa_usr1));
	ft_bzero(&sa_usr2, sizeof(sa_usr2));
	sa_usr1.sa_sigaction = signal_action;
	sa_usr2.sa_sigaction = signal_action;
	sa_usr1.sa_flags = SA_SIGINFO;
	sa_usr2.sa_flags = SA_SIGINFO;
	if (sigemptyset(&sa_usr1.sa_mask) < 0)
		exit_with_error(SIGEMPTYSET_FAIL);
	if (sigemptyset(&sa_usr2.sa_mask) < 0)
		exit_with_error(SIGEMPTYSET_FAIL);
	if (sigaddset(&sa_usr1.sa_mask, SIGUSR2) < 0)
		exit_with_error(SIGADDSET_FAIL);
	if (sigaddset(&sa_usr2.sa_mask, SIGUSR1) < 0)
		exit_with_error(SIGADDSET_FAIL);
	if (sigaction(SIGUSR1, &sa_usr1, NULL) < 0)
		exit_with_error(SIGACTION_FAIL);
	if (sigaction(SIGUSR2, &sa_usr2, NULL) < 0)
		exit_with_error(SIGACTION_FAIL);
}
