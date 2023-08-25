/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_with_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 00:06:29 by sakitaha          #+#    #+#             */
/*   Updated: 2023/08/26 04:10:25 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	exit_with_error(t_error_type error_type)
{
	char	*message[ERROR_TYPE_COUNT];

	message[SIGEMPTYSET_FAIL] = "Error: Failed to initialize signal set";
	message[SIGACTION_FAIL] = "Error: Failed to set signal handler";
	message[MALLOC_FAIL] = "Error: Failed to allocate memory";
	message[KILL_FAIL] = "Error: Failed to send signal";
	message[INVALID_ARGS] = "Usage: ./client [server PID] [message]";
	message[INVALID_PID] = "Error: Invalid PID";
	message[INVALID_STRING] = "Error: Invalid string";
	message[INVALID_CHAR] = "Error: Invalid char";
	message[TIMEOUT] = "Error: Timeout";
	if (error_type < ERROR_TYPE_COUNT)
		ft_putendl_fd(message[error_type], 2);
	else
		ft_putendl_fd("Error: Unknown error", 2);
	exit(EXIT_FAILURE);
}
