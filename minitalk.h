/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 04:12:35 by sakitaha          #+#    #+#             */
/*   Updated: 2023/08/24 07:12:00 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "./libft/libft.h"
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <unistd.h>

# define SLEEP_DURATION 1000
# define TIMEOUT_LIMIT 1000000

typedef enum e_error_type
{
	SIGEMPTYSET_FAIL,
	SIGACTION_FAIL,
	INVALID_ARGS,
	INVALID_PID,
	INVALID_STRING,
	INVALID_CHAR,
	KILL_FAIL,
	TIMEOUT,
	ERROR_TYPE_COUNT
}							t_error_type;

typedef struct s_signal_data
{
	volatile sig_atomic_t	current_pid;
	volatile sig_atomic_t	signal_status;
}							t_signal_data;

bool						is_arg_numeric(const char *str);
void						exit_with_error(t_error_type error_type);
void						init_sig(void (*action)(int, siginfo_t *, void *));

#endif
