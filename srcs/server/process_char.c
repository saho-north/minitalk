/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 21:57:01 by sakitaha          #+#    #+#             */
/*   Updated: 2023/11/08 22:10:19 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	double_buffer_size(t_msg_state *msg_state)
{
	char	*tmp;
	size_t	new_buf_size;

	new_buf_size = msg_state->buf_size * 2;
	tmp = (char *)ft_realloc(msg_state->buf, msg_state->buf_size, new_buf_size);
	if (!tmp)
	{
		notify_failure(msg_state);
		free_and_exit(msg_state, MALLOC_FAIL);
	}
	msg_state->buf = tmp;
	msg_state->buf_size = new_buf_size;
}

static void	handle_message_completion(t_msg_state *msg_state)
{
	write(1, msg_state->buf, msg_state->buf_index);
	msg_state->is_end_of_message = true;
}

static void	append_char(t_msg_state *msg_state)
{
	msg_state->buf[msg_state->buf_index] = msg_state->current_char;
	msg_state->buf_index++;
}

static void	ensure_buf_capacity(t_msg_state *msg_state)
{
	if (msg_state->buf_index < msg_state->buf_size)
		return ;
	double_buffer_size(msg_state);
}

void	process_char(t_msg_state *msg_state)
{
	ensure_buf_capacity(msg_state);
	append_char(msg_state);
	if (msg_state->current_char == '\0')
		handle_message_completion(msg_state);
	msg_state->current_char = 0;
	msg_state->bits_count = 0;
}
