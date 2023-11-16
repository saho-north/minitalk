/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 04:12:35 by sakitaha          #+#    #+#             */
/*   Updated: 2023/11/13 21:04:55 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "libft.h"
# include <signal.h>
# include <stddef.h>
# include <unistd.h>

# define SLEEP_DURATION 100
# define ZERO 0
# define ONE 1
# define IDLE -1

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

extern volatile sig_atomic_t	g_signal_pid_state;

void							exit_with_error(t_error_type error_type);
void							init_sigaction(void (*a)(int, siginfo_t *,
										void *));

#endif
