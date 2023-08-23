/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 03:56:21 by sakitaha          #+#    #+#             */
/*   Updated: 2023/08/24 05:22:52 by sakitaha         ###   ########.fr       */
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

static volatile t_signal_data	g_client_status;

static void	signal_action(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	if (g_client_status.signal_status != SIG_FOR_WAITING)
	{
		return ;
	}
	if (g_client_status.current_pid == 0)
	{
		g_client_status.current_pid = info->si_pid;
	}
	else if (info->si_pid != g_client_status.current_pid)
	{
		return ;
	}
	if (sig == SIGUSR1)
	{
		g_client_status.signal_status = SIG_FOR_ZERO_BIT;
	}
	else if (sig == SIGUSR2)
	{
		g_client_status.signal_status = SIG_FOR_ONE_BIT;
	}
}

/*
int	main(void)
{
    initialize_server(); // 初期化関数
    while (1)
    {
        usleep(SLEEP_DURATION);
        handle_bit(); // ビット処理関数
        confirm_message(); // メッセージ送信確認関数
    }
    return (0);
}
 */

void	initialize_server(void)
{
	g_client_status.current_pid = 0;
	g_client_status.signal_status = SIG_FOR_WAITING;
	init_sigaction(signal_action);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
}

int	main(void)
{
	bool					is_end_of_transmission;
	char					current_char;
	volatile sig_atomic_t	handled_bits_count;

	initialize_server();
	is_end_of_transmission = false;
	current_char = 0;
	handled_bits_count = 0;
	while (1)
	{
		usleep(SLEEP_DURATION);
		if (g_client_status.signal_status != SIG_FOR_WAITING)
		{
			if (g_client_status.signal_status == SIG_FOR_ONE_BIT)
			{
				current_char |= 1 << (7 - handled_bits_count);
			}
			handled_bits_count++;
			if (handled_bits_count == 8)
			{
				if (current_char != 0x02 && current_char != 0x03)
					write(1, &current_char, 1);
				else if (current_char == 0x03)
				{
					write(1, "\n", 1);
					is_end_of_transmission = true;
				}
				current_char = 0;
				handled_bits_count = 0;
			}
			g_client_status.signal_status = SIG_FOR_WAITING;
			if (kill(g_client_status.current_pid, SIGUSR2) < 0)
				exit_with_error(KILL_FAIL);
			if (is_end_of_transmission)
			{
				g_client_status.current_pid = 0;
				is_end_of_transmission = false;
			}
		}
	}
	return (0);
}
