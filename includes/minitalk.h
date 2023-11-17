/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 04:12:35 by sakitaha          #+#    #+#             */
/*   Updated: 2023/11/17 14:44:33 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "libft.h"
# include <signal.h>
# include <stddef.h>
# include <unistd.h>

typedef enum e_error_type
{
	MALLOC_FAIL,
	KILL_FAIL,
	INVALID_ARGS,
	INVALID_PID,
	INVALID_TXT,
	INVALID_CHAR,
	TIMEOUT,
	SERVER_FAIL,
	ERROR_TYPE_COUNT
}								t_error_type;

/*
 * Project constraints limit to one global variable per server/client program.
 * The g_signal_pid_state variable serves two purposes:
 * 1. Stores the PID to verify the signal sender's validity.
 * 2. Holds a received signal as a flag for notifying the main component.
 */

extern volatile sig_atomic_t	g_signal_pid_state;

void							exit_with_error(t_error_type error_type);
void							init_sigaction(void (*a)(int, siginfo_t *,
										void *));

#endif
