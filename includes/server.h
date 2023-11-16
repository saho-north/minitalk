/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 01:30:53 by sakitaha          #+#    #+#             */
/*   Updated: 2023/11/17 01:55:02 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include "minitalk.h"

# define INITIAL_BUF_SIZE 1024
# define MAX_INVALID_SIGNALS 1000

typedef enum e_signal_status
{
	ZERO = 0,
	ONE = 1,
	IDLE = -1
}								t_signal_status;

typedef struct s_msg_state
{
	char						*buf;
	size_t						buf_index;
	size_t						buf_size;
	char						current_char;
	size_t						bits_count;
	pid_t						sender_pid;
	size_t						invalid_signal_count;
	bool						is_end_of_message;
}								t_msg_state;

extern volatile sig_atomic_t	g_signal_pid_state;

void							reset_server(void);
void							reset_msg_state(t_msg_state *msg_state);
void							receive_message(t_msg_state *msg_state);
void							process_char(t_msg_state *msg_state);
bool							is_server_idle(void);
bool							has_pid(void);
bool							has_signal(void);
void							handle_signal_overflow(t_msg_state *msg_state);
void							free_and_exit(t_msg_state *m, t_error_type e);
void							notify_failure(t_msg_state *msg_state);

#endif
