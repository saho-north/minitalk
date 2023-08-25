/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_bit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 07:29:24 by sakitaha          #+#    #+#             */
/*   Updated: 2023/08/26 04:04:53 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static char	*process_start_of_txt(size_t *buf_size, size_t *buf_index)
{
	char	*buf;

	buf = (char *)malloc(sizeof(char) * INITIAL_BUF_SIZE + 1);
	if (!buf)
		exit_with_error(MALLOC_FAIL);
	*buf_size = INITIAL_BUF_SIZE;
	*buf_index = 0;
	return (buf);
}

static void	process_end_of_txt(char *buf, size_t buf_index)
{
	buf[buf_index] = '\0';
	write(1, buf, buf_index);
	write(1, "\n", 1);
	free(buf);
	buf = NULL;
	g_client_info.current_pid = 0;
}

static void	confirm_char(char current_char)
{
	static char		*buf;
	static size_t	buf_size;
	static size_t	buf_index;
	char			*old_buf;

	if (current_char == START_OF_TXT)
		buf = process_start_of_txt(&buf_size, &buf_index);
	else if (current_char == END_OF_TXT)
		process_end_of_txt(buf, buf_index);
	else
	{
		if (buf_index >= buf_size)
		{
			old_buf = buf;
			buf = (char *)ft_realloc(buf, buf_size, buf_size * 2 + 1);
			if (!buf)
			{
				free(old_buf);
				exit_with_error(MALLOC_FAIL);
			}
			buf_size *= 2;
		}
		buf[buf_index] = current_char;
		buf_index++;
	}
}

static void	process_bit(char *current_char, size_t *bits_count)
{
	if (g_client_info.signal_status == SIG_FOR_ONE_BIT)
	{
		*current_char |= 1 << (7 - *bits_count);
	}
	(*bits_count)++;
}

void	handle_bit(void)
{
	static char		current_char;
	static size_t	bits_count;
	pid_t			client_pid;

	client_pid = g_client_info.current_pid;
	if (client_pid == 0)
	{
		current_char = 0;
		bits_count = 0;
		return ;
	}
	if (g_client_info.signal_status == SIG_FOR_WAITING)
		return ;
	process_bit(&current_char, &bits_count);
	if (bits_count == 8)
	{
		confirm_char(current_char);
		current_char = 0;
		bits_count = 0;
	}
	g_client_info.signal_status = SIG_FOR_WAITING;
	if (kill(client_pid, SIGUSR2) < 0)
		exit_with_error(KILL_FAIL);
}
