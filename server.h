/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 06:39:25 by sakitaha          #+#    #+#             */
/*   Updated: 2023/08/24 14:49:59 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include "minitalk.h"

typedef enum e_bit_signal
{
	SIG_FOR_ZERO_BIT,
	SIG_FOR_ONE_BIT,
	SIG_FOR_WAITING
}								t_bit_signal;

extern volatile t_signal_info	g_client_info;

void							handle_bit(void);
#endif
