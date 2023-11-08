/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 04:12:35 by sakitaha          #+#    #+#             */
/*   Updated: 2023/11/08 13:42:22 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "libft.h"
# include <signal.h>
# include <stddef.h>
# include <unistd.h>

# define SLEEP_DURATION 100

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
}							t_error_type;

typedef struct s_signal_info
{
	volatile sig_atomic_t	current_pid;
	volatile sig_atomic_t	signal_status;
}							t_signal_info;

void						exit_with_error(t_error_type error_type);
void						init_sigaction(void (*a)(int, siginfo_t *, void *));

#endif
