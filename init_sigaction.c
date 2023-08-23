/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sigaction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 01:27:45 by sakitaha          #+#    #+#             */
/*   Updated: 2023/08/23 02:44:47 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	init_sigaction(void (*signal_action)(int, siginfo_t *, void *))
{
	struct sigaction	sa;

	bzero(&sa, sizeof(sa));
	sa.sa_sigaction = signal_action;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) < 0)
		exit_with_error(SIGACTION_FAIL);
	if (sigaction(SIGUSR2, &sa, NULL) < 0)
		exit_with_error(SIGACTION_FAIL);
}
