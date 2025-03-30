/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str2d_join.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 20:17:05 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/25 20:25:49 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	join2d(char **join, char **str1, char **str2)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (str1[++i] != NULL)
	{
		join[++j] = ft_strdup(str1[i]);
		if (join[j] == NULL)
			return (free_tab(join), EXIT_FAILURE);
	}
	i = -1;
	while (str2[++i] != NULL)
	{
		join[++j] = ft_strdup(str2[i]);
		if (join[j] == NULL)
			return (free_tab(join), EXIT_FAILURE);
	}
	join[++j] = NULL;
	return (EXIT_SUCCESS);
}

char	**strdup2d(char **str)
{
	char	**res;
	int		i;

	res = ft_malloc(sizeof(char *) * (ft_strlen_2d(str) + 1));
	if (res == NULL)
		return (NULL);
	i = -1;
	while (str[++i] != NULL)
	{
		res[i] = ft_strdup(str[i]);
		if (res[i] == NULL)
			return (free_tab(res), NULL);
	}
	res[i] = NULL;
	return (res);
}

char	**str2d_join(char **str1, char **str2)
{
	char	**join;

	if (str1 == NULL || str2 == NULL)
		return (NULL);
	if (str2 == NULL && str1 != NULL)
		return (str2 = strdup2d(str1), str2);
	if (str1 == NULL && str2 != NULL)
		return (str1 = strdup2d(str2), str1);
	join = ft_malloc(sizeof(char *) * (ft_strlen_2d(str1) + ft_strlen_2d(str2)
				+ 1));
	if (join == NULL)
		return (NULL);
	if (join2d(join, str1, str2) == EXIT_FAILURE)
		return (NULL);
	return (join);
}

char	**re_str2djoin(char **str1, char **str2)
{
	char	**join;

	if (str1 == NULL && str2 == NULL)
		return (NULL);
	if (str2 == NULL && str1 != NULL)
		return (str2 = strdup2d(str1), free_tab(str1), str2);
	if (str1 == NULL && str2 != NULL)
		return (strdup2d(str2));
	join = ft_malloc(sizeof(char *) * (ft_strlen_2d(str1) + ft_strlen_2d(str2)
				+ 1));
	if (join == NULL)
		return (free_tab(str1), NULL);
	if (join2d(join, str1, str2) == EXIT_FAILURE)
		return (free_tab(str1), NULL);
	return (free_tab(str1), join);
}
