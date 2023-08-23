/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 04:12:35 by sakitaha          #+#    #+#             */
/*   Updated: 2023/08/24 00:56:04 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "./libft/libft.h"
# include <signal.h>
# include <stdbool.h>
# include <unistd.h>

# define SLEEP_DURATION 1000
# define TIMEOUT_LIMIT 1000000

typedef enum e_signal_acknowledgement
{
	ACK_SERVER_BUSY,
	ACK_RECEIVED,
	ACK_TIME_OUT,
	ACK_WAITING
}		t_signal_acknowledgement;

typedef enum e_error_type
{
	SIGEMPTYSET_FAIL,
	SIGACTION_FAIL,
	NOT_VALID_ARGS,
	NOT_VALID_PID,
	NOT_VALID_STRING,
	NOT_VALID_CHAR,
	KILL_FAIL,
	TIMEOUT,
	ERROR_TYPE_COUNT
}		t_error_type;

bool	is_arg_numeric(const char *str);
void	exit_with_error(t_error_type error_type);
void	init_sigaction(void (*signal_action)(int, siginfo_t *, void *));

#endif
