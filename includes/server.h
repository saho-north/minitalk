/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 01:30:53 by sakitaha          #+#    #+#             */
/*   Updated: 2023/09/01 05:44:54 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include "minitalk.h"

# define INITIAL_BUF_SIZE 1024
# define CALL_LIMIT 1000

typedef enum e_signal_status
{
	ZERO_BIT,
	ONE_BIT,
	WAITING_FOR_SIGNAL
}								t_signal_status;

typedef struct s_msg_state
{
	char						*buf;
	size_t						buf_index;
	size_t						buf_size;
	char						current_char;
	size_t						bits_count;
	pid_t						sender_pid;
	size_t						call_count;
	bool						is_first_signal;
	bool						is_last_signal;
}								t_msg_state;

extern volatile t_signal_info	g_server_info;

void							reset_server_info(void);
void							reset_msg_state(t_msg_state *msg_state);
void							receive_message(t_msg_state *msg_state);
void							put_char_into_buf(t_msg_state *msg_state);
bool							has_no_current_client(void);
bool							is_waiting_signal(void);
void							check_call_limit(t_msg_state *msg_state);
void							free_and_exit(t_msg_state *m, t_error_type e);

#endif
