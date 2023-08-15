/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 04:31:32 by sakitaha          #+#    #+#             */
/*   Updated: 2023/08/15 14:48:55 by sakitaha         ###   ########.fr       */
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
 */

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
	if (argc != 3 || !is_valid_pid(argv[1]))
	{
		ft_putstr_fd("Error: Invalid arguments\n", 2);
		ft_putstr_fd("Usage: ./client [server PID] [message]\n", 2);
		return (1);
	}
	return (0);
}

/*
Chapter V Bonus part
Bonus list:
• The server acknowledges every message received by sending back a signal to the client.
• Unicode characters support!
 */
