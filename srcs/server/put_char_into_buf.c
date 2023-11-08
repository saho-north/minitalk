/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_char_into_buf.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 01:50:51 by sakitaha          #+#    #+#             */
/*   Updated: 2023/11/08 12:26:35 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	realloc_msg_state(t_msg_state *msg_state)
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

static void	append_char(t_msg_state *msg_state)
{
	if (msg_state->is_first_signal || msg_state->is_last_signal)
	{
		notify_failure(msg_state);
		free_and_exit(msg_state, INVALID_TXT);
	}
	if (msg_state->buf_index + 2 >= msg_state->buf_size)
		realloc_msg_state(msg_state);
	msg_state->buf[msg_state->buf_index] = msg_state->current_char;
	msg_state->buf_index++;
}

static void	process_end_of_txt(t_msg_state *msg_state)
{
	msg_state->buf[msg_state->buf_index] = '\0';
	write(1, msg_state->buf, msg_state->buf_index);
	msg_state->is_last_signal = true;
}

static void	process_start_of_txt(t_msg_state *msg_state)
{
	if (!msg_state->is_first_signal)
	{
		notify_failure(msg_state);
		free_and_exit(msg_state, INVALID_TXT);
	}
	msg_state->is_first_signal = false;
}

void	put_char_into_buf(t_msg_state *msg_state)
{
	if (msg_state->current_char == START_OF_TXT)
		process_start_of_txt(msg_state);
	else if (msg_state->current_char == END_OF_TXT)
		process_end_of_txt(msg_state);
	else
		append_char(msg_state);
}
