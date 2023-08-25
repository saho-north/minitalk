/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_bit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 07:29:24 by sakitaha          #+#    #+#             */
/*   Updated: 2023/08/25 18:03:17 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#define INITIAL_BUF_SIZE 1024

static void	process_bit(char *current_char, size_t *bits_count)
{
	if (g_client_info.signal_status == SIG_FOR_ONE_BIT)
	{
		*current_char |= 1 << (7 - *bits_count);
	}
	(*bits_count)++;
}

static void	confirm_char(char *current_char, size_t *bits_count)
{
	static char		*buf;
	static size_t	buf_size;
	static size_t	buf_index;
	char			*old_buf;

	if (*bits_count == 8)
	{
		if (*current_char == START_OF_TXT)
		{
			buf = (char *)malloc(sizeof(char) * INITIAL_BUF_SIZE + 1);
			if (!buf)
				exit_with_error(MALLOC_FAIL);
			buf_size = INITIAL_BUF_SIZE;
			buf_index = 0;
		}
		else if (*current_char == END_OF_TXT)
		{
			buf[buf_index] = '\0';
			write(1, buf, buf_index);
			write(1, "\n", 1);
			free(buf);
			buf = NULL;
			g_client_info.current_pid = 0;
		}
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
			buf[buf_index] = *current_char;
			buf_index++;
		}
		*current_char = 0;
		*bits_count = 0;
	}
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
	{
		return ;
	}
	process_bit(&current_char, &bits_count);
	confirm_char(&current_char, &bits_count);
	g_client_info.signal_status = SIG_FOR_WAITING;
	if (kill(client_pid, SIGUSR2) < 0)
		exit_with_error(KILL_FAIL);
}
