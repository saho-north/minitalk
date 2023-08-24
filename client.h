/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 06:28:54 by sakitaha          #+#    #+#             */
/*   Updated: 2023/08/24 21:01:42 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include "minitalk.h"

# define MAX_RETRIES 10

typedef enum e_signal_acknowledgement
{
	ACK_SERVER_BUSY,
	ACK_RECEIVED,
	ACK_TIME_OUT,
	ACK_WAITING
}								t_signal_acknowledgement;

extern volatile t_signal_info	g_client_info;

bool							is_arg_numeric(const char *str);

#endif
