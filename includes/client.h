/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 06:28:54 by sakitaha          #+#    #+#             */
/*   Updated: 2023/11/17 15:43:25 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include "minitalk.h"
# include <stdbool.h>

# define MAX_ATTEMPTS 10
# define TIMEOUT_LIMIT 1000000
# define SLEEP_DURATION 100
# define IDLE -1

typedef enum e_signal_acknowledgement
{
	ACK_SERVER_FAIL,
	ACK_RECEIVED
}				t_signal_acknowledgement;

void			transmit_message(pid_t pid, const char *str);
sig_atomic_t	get_ack_status(void);

#endif
