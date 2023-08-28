/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 06:39:25 by sakitaha          #+#    #+#             */
/*   Updated: 2023/08/29 05:30:05 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include "minitalk.h"

# define INITIAL_BUF_SIZE 1024

typedef enum e_signal_status
{
	SIG_FOR_WAITING,
	SIG_FOR_ZERO_BIT,
	SIG_FOR_ONE_BIT,
	SIG_READY_FOR_NEW_CLIENT,
	SIG_COMMUNICATION_ERROR_SERVER,
	SIG_COMMUNICATION_ERROR_CLIENT,
	SIG_TIMEOUT,
	SIG_KILL_ERROR
}								t_signal_status;

extern volatile t_signal_info	g_server_info;

#endif
