/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_2d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 19:43:30 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/25 20:31:21 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen_2d(char **tab)
{
	int	count;

	count = 0;
	if (tab == NULL)
		return (0);
	while (tab[count])
		count++;
	return (count);
}
