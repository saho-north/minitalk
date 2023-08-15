/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 03:56:21 by sakitaha          #+#    #+#             */
/*   Updated: 2023/08/15 12:34:38 by sakitaha         ###   ########.fr       */
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
 */

int	main(void)
{
	printf("server pid: %d\n", getpid());
	//receive signal from client
	//signal() returns the previous value of the signal handler,
	//	or SIG_ERR on error.
	// SIGUSR1: user-defined signal 1
	// SIGUSR2: user-defined signal 2
	// print the string received from client
	return (0);
}

/*
Chapter V Bonus part
Bonus list:
• The server acknowledges every message received by sending back a signal to the client.
• Unicode characters support!
 */
