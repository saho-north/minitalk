/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 04:12:35 by sakitaha          #+#    #+#             */
/*   Updated: 2023/08/18 02:52:26 by sakitaha         ###   ########.fr       */
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

bool	is_valid_pid(const char *str);

#endif
