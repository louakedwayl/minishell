/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strrdup_add_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:28:34 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/20 21:51:47 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/minishell.h"

static char	**first_line(char ***rettab, char **s, char *new)
{
	if (!s)
	{
		*rettab = ft_calloc (sizeof(char *), (2));
		if (!(*rettab))
			return (NULL);
		(*rettab)[0] = ft_strdup(new);
		if (!(*rettab)[0])
		{
			ft_free (*rettab);
			return (NULL);
		}
		return (*rettab);
	}
	return (NULL);
}

static void	init_i(char **s, int *i)
{
	while (s[*i])
		(*i)++;
}

char	**strrdup_add_line(char **s, char *new)
{
	char	**rettab;
	int		i;

	i = 0;
	rettab = first_line(&rettab, s, new);
	if (rettab)
		return (rettab);
	init_i(s, &i);
	rettab = ft_calloc(sizeof(char *), (i + 2));
	if (!rettab)
		return (NULL);
	i = 0;
	while (s[i])
	{
		rettab[i] = ft_strdup(s[i]);
		if (!rettab[i])
		{
			free_tab(rettab);
			return (NULL);
		}
		i++;
	}
	free_tab(s);
	rettab[i] = ft_strdup(new);
	return (rettab);
}
