/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 03:56:21 by sakitaha          #+#    #+#             */
/*   Updated: 2023/08/17 19:01:34 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>

// only one global variable is allowed for signal handler?
//static int	g_sig = 0;

/*
• In order to complete the mandatory part,
	you are allowed to use the following functions:
◦ write
◦ ft_printf and any equivalent YOU coded ◦ signal
◦ sigemptyset
◦ sigaddset
◦ sigaction
◦ kill
◦ getpid
◦ malloc
◦ free
◦ pause
◦ sleep
◦ usleep
◦ exit

Mandatory Part
You must create a communication program in the form of a client and a server.
• The server must be started first. After its launch, it has to print its PID.

• The client must send the string passed as a parameter to the server.
Once the string has been received, the server must print it.

• The server has to display the string pretty quickly.
Quickly means that if you think it takes too long, then it is probably too long.

• Your server should be able to receive strings from several clients in a row without needing to restart.
• The communication between your client and your server has to be done only using UNIX signals.
• You can only use these two signals: SIGUSR1 and SIGUSR2.
1 second for displaying 100 characters is way too much!
Linux system does NOT queue signals when you already have pending signals of this type!  Bonus time?

Chapter V Bonus part
Bonus list:
• The server acknowledges every message received by sending back a signal to the client.
• Unicode characters support!
 */

static void	signal_action(int sig, siginfo_t *info, void *ucontext)
{
	static size_t	bits_count;
	static char		current_char;

	(void)ucontext;
	(void)info;
	//printf("before sig: %d, bits_count: %zu, current_char: %c\n", sig,
	//	bits_count, current_char);
	//printf("sig: %d, bits_count: %zu, current_char: %c\n", sig, bits_count,
	//	current_char);
	if (sig == SIGUSR1)
	{
		//printf("sig == SIGUSR1\n");
		current_char = (current_char << 1) | 1;
	}
	else if (sig == SIGUSR2)
	{
		//printf("sig == SIGUSR2\n");
		current_char = (current_char << 1) | 0;
	}
	bits_count++;
	/* printf("after  sig: %d, bits_count: %zu, current_char: %c\n\n", sig,
			bits_count, current_char);
		*/
	if (bits_count == 8)
	{
		if (write(1, &current_char, 1) == -1)
		{
			ft_putendl_fd("Error: write failed", 2);
			exit(1);
		}
		current_char = 0;
		bits_count = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;
	pid_t				pid;

	sa.sa_sigaction = signal_action;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) < 0 || sigaction(SIGUSR2, &sa, NULL) < 0)
	{
		ft_putendl_fd("Error: sigaction failed", 2);
		return (1);
	}
	pid = getpid();
	ft_putnbr_fd(pid, 1);
	//ft_putchar_fd('\n', 1);
	while (1)
		pause();
	return (0);
}
