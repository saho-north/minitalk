/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_bi_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 23:00:17 by sakitaha          #+#    #+#             */
/*   Updated: 2023/08/18 23:51:21 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

//デバッグ用

void	write_binary_char(char c, int fd)
{
	char	buffer[8];

	for (int i = 0; i < 8; i++)
	{
		buffer[7 - i] = (c & (1 << i)) ? '1' : '0';
	}
	write(fd, buffer, 8); // バッファを書き込み
}