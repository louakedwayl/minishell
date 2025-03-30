/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:31:02 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/22 18:22:26 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/minishell.h"
#include "libft.h"

int	size_before_equal(char *string)
{
	int	i;

	i = 0;
	while (string[i] && string[i] != '=')
		i++;
	return (i);
}

int	check_format_var(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		while (ft_isprint(string[i]) && string[i] != '=' )
			i++;
		if (string[i] == '=' && i != 0)
			i++;
		else
			return (EXIT_FAILURE);
		if (ft_isprint(string[i]))
			return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

char	**split_name_value(char *arg)
{
	char	**dest;

	dest = ft_malloc(sizeof(char *) * 3);
	if (dest == NULL)
		return (NULL);
	dest[0] = ft_substr(arg, 0, size_before_equal(arg));
	if (dest[0] == NULL)
		return (NULL);
	if (ft_strchr(arg, '=') == NULL)
		dest[1] = NULL;
	else
	{
		dest[1] = ft_strdup(ft_strchr(arg, '=') + 1);
		if (dest[1] == NULL)
			return (NULL);
	}
	dest[2] = NULL;
	return (dest);
}
