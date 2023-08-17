/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 04:31:32 by sakitaha          #+#    #+#             */
/*   Updated: 2023/08/17 17:25:11 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>

// one global variable allowed for communication between the handler and the main program
//static int	g_sig;

/*
• In order to complete the mandatory part,
	you are allowed to use the following functions:
◦ write
◦ ft_printf and any equivalent YOU coded
◦ signal
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

• The client takes two parameters:
	◦ The server PID.
	◦ The string to send.

• The client must send the string passed as a parameter to the server.
Once the string has been received, the server must print it.

• The server has to display the string pretty quickly.
Quickly means that if you think it takes too long, then it is probably too long.

• The communication between your client and your server has to be done only using UNIX signals.
• You can only use these two signals: SIGUSR1 and SIGUSR2.
1 second for displaying 100 characters is way too much!
Linux system does NOT queue signals when you already have pending
signals of this type!  Bonus time?


Chapter V Bonus part
Bonus list:
• The server acknowledges every message received by sending back a signal to the client.
• Unicode characters support!

 */

static void	transmit_char(pid_t pid, char c)
{
	size_t	bit_index;

	bit_index = 8;
	while (bit_index-- > 0)
	{
		if ((c >> bit_index) & 1)
		{
			if (kill(pid, SIGUSR2) < 0)
			{
				ft_putendl_fd("Error: Failed to send signal", 2);
				exit(1);
			}
		}
		else
		{
			if (kill(pid, SIGUSR1) < 0)
			{
				ft_putendl_fd("Error: Failed to send signal", 2);
				exit(1);
			}
		}
		usleep(SLEEP_DURATION);
	}
}

static void	send_message(pid_t pid, const char *str)
{
	while (*str)
	{
		transmit_char(pid, *str);
		str++;
	}
	transmit_char(pid, 0x03);
}

static bool	is_valid_pid(const char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

int	main(int argc, char const *argv[])
{
	pid_t	pid;

	if (argc != 3 || !is_valid_pid(argv[1]))
	{
		ft_putendl_fd("Error: Invalid arguments", 2);
		ft_putendl_fd("Usage: ./client [server PID] [message]", 2);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	if (kill(pid, 0) < 0)
	{
		ft_putendl_fd("Error: Invalid PID", 2);
		return (1);
	}
	send_message(pid, argv[2]);
	return (0);
}
