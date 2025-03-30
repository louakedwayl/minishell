/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_string_char_2d.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 20:15:54 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/25 20:29:52 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	add_string_char_2d(char ***tab, char *str)
{
	char	**new;
	int		count;
	char	**buffer;

	buffer = *tab;
	new = ft_malloc(sizeof(char *) * (ft_strlen_2d(buffer) + 1 + 1));
	if (!new)
		return (-1);
	count = 0;
	while (buffer && buffer[count])
	{
		new[count] = buffer[count];
		count++;
	}
	new[count] = str;
	new[++count] = NULL;
	ft_free(buffer);
	*tab = new;
	return (EXIT_SUCCESS);
}
