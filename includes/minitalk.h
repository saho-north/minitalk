/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 04:12:35 by sakitaha          #+#    #+#             */
/*   Updated: 2023/08/26 05:10:51 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "libft.h"
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <unistd.h>

# define SLEEP_DURATION 100

typedef enum e_error_type
{
	SIGEMPTYSET_FAIL,
	SIGACTION_FAIL,
	MALLOC_FAIL,
	KILL_FAIL,
	INVALID_ARGS,
	INVALID_PID,
	INVALID_STRING,
	INVALID_CHAR,
	TIMEOUT,
	ERROR_TYPE_COUNT
}							t_error_type;

typedef enum e_control_characters
{
	START_OF_TXT = 0x02,
	END_OF_TXT = 0x03
}							t_control_characters;

typedef struct s_signal_data
{
	volatile sig_atomic_t	current_pid;
	volatile sig_atomic_t	signal_status;
}							t_signal_info;

void						exit_with_error(t_error_type error_type);
void						init_sigaction(void (*a)(int, siginfo_t *, void *));

#endif
