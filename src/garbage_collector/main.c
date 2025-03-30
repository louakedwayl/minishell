/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 20:17:38 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/25 20:25:16 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"

int	main(int argc, char **argv)
{
	int		i;
	char	*ptr;

	i = 0;
	(void)argv;
	(void)argc;
	while (i < 100)
	{
		ptr = ft_malloc(100);
		if (i % 2 != 0)
			lock(ptr);
		i++;
	}
	soft_clear();
	clear_all();
}
