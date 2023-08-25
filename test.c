/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 04:23:50 by sakitaha          #+#    #+#             */
/*   Updated: 2023/08/25 05:05:01 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>

// int	main(int argc, char const *argv[])
// {
// 	unsigned char	*str;

// 	(void)argc;
// 	(void)argv;
// 	str = (unsigned char *)"😀";
// 	printf("%s\n", str);
// 	for (int i = 0; str[i]; i++)
// 	{
// 		printf("%x\n", str[i]);
// 	}
// 	return (0);
// }
#include <stdio.h>
#include <stdlib.h>

const char	*env_vars[] = {"LC_ALL", "LC_CTYPE", "LANG"};

int	main(void)
{
	char	*lang;

	lang = NULL;
	for (int i = 0; i < sizeof(env_vars) / sizeof(env_vars[0]); i++)
	{
		lang = getenv(env_vars[i]);
		if (lang != NULL)
		{
			break ;
		}
	}
	if (lang != NULL)
	{
		printf("Current encoding setting: %s\n", lang);
	}
	else
	{
		printf("Encoding settings are not set.\n");
	}
	return (0);
}
