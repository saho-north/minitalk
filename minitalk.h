/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 04:12:35 by sakitaha          #+#    #+#             */
/*   Updated: 2023/08/19 03:51:43 by sakitaha         ###   ########.fr       */
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

//後でtimeoutの実装を行う
typedef enum e_signal_acknowledgement
{
	SERVER_BUSY,
	SIGNAL_RECEIVED,
	WAITING_FOR_ACK
}		t_signal_acknowledgement;

bool	is_valid_pid(const char *str);
//デバッグ用
void	write_binary_char(char c, int fd);

#endif
