/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 03:56:21 by sakitaha          #+#    #+#             */
/*   Updated: 2023/08/23 23:01:25 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
Project instructions
• Name your executable files client and server.
• You have to turn in a Makefile which will compile your source files. It must not
relink.
• You can definitely use your libft.
• You have to handle errors thoroughly. In no way your program should quit unex- pectedly (segmentation fault,
		bus error, double free, and so forth).
• Your program mustn’t have memory leaks.
• You can have one global variable per program (one for the client and one for
the server), but you will have to justify their use.
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
• The client takes two parameters: ◦ The server PID.
◦ The string to send.
• The client must send the string passed as a parameter to the server.
Once the string has been received, the server must print it.
• The server has to display the string pretty quickly. Quickly means that if you think it takes too long,
	then it is probably too long.
• Your server should be able to receive strings from several clients in a row without needing to restart.
• The communication between your client and your server has to be done only using UNIX signals.
• You can only use these two signals: SIGUSR1 and SIGUSR2.
1 second for displaying 100 characters is way too much!
Linux system does NOT queue signals when you already have pending
signals of this type!  Bonus time?

Bonus part
Bonus list:
• The server acknowledges every message received by sending back a signal to the client.
• Unicode characters support!
 */

typedef struct s_client_info
{
	volatile sig_atomic_t		client_pid;
}								t_client_info;

static volatile t_client_info	g_client_info;

static void	signal_action(int sig, siginfo_t *info, void *ucontext)
{
	static volatile sig_atomic_t	bits_count;
	static volatile sig_atomic_t	current_char;
	char							tmp;

	(void)ucontext;
	if (g_client_info.client_pid == 0)
	{
		//初回の呼び出しについて、client_pidを設定する
		g_client_info.client_pid = info->si_pid;
	}
	else if (info->si_pid != g_client_info.client_pid)
	{
		//client_pidが設定されている場合、それ以外のPIDからのシグナルは無視する
		return ;
	}
	if (kill(info->si_pid, SIGUSR2) < 0)
		exit_with_error(KILL_FAIL);
	if (sig == SIGUSR2)
	{
		current_char |= 1 << (7 - bits_count);
	}
	bits_count++;
	if (bits_count == 8)
	{
		tmp = current_char;
		if (tmp != 0x02 && tmp != 0x03)
			write(1, &tmp, 1);
		else if (tmp == 0x03)
		{
			write(1, "\n", 1);
			g_client_info.client_pid = 0;
		}
		current_char = 0;
		bits_count = 0;
	}
}

int	main(void)
{
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	init_sigaction(signal_action);
	while (1)
		pause();
	return (0);
}
