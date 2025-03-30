/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 20:18:15 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/25 20:24:39 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_to_next_char(char *str, int i, char c)
{
	int	len;

	len = 1;
	while (str[i + len] != c)
		len++;
	len++;
	return (len);
}

char	**split_expand(char *to_split)
{
	char	**split;
	int		i;
	int		len;

	i = 0;
	split = NULL;
	while (to_split[i])
	{
		while (is_in_charset(to_split[i], " \t") == true && to_split[i])
			i++;
		len = 0;
		while (!is_in_charset(to_split[i + len], " \t") && to_split[i + len])
		{
			if (to_split[i + len] == '"' || to_split[i + len] == '\'')
				len += len_to_next_char(to_split, i + len, to_split[i + len]);
			else
				len++;
		}
		if (!is_in_charset(to_split[i + len - 1], " \t"))
			add_string_char_2d(&split, ft_substr(to_split, i, len));
		i += len;
	}
	return (split);
}

bool	is_variable_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}

void	add_until_dollard(char **dest, char *str, int *i)
{
	int		len;
	char	*substr;

	len = 0;
	while (str[*i + len] && str[*i + len] != '$')
		len++;
	substr = ft_substr(str, *i, len);
	*dest = ft_re_strjoin(*dest, substr);
	ft_free(substr);
	*i += len;
}

char	*extract_variable(char *str, int *start)
{
	int		len;
	char	*variable;

	len = 0;
	(*start)++;
	if (str[*start] == '?')
		return ((*start)++, ft_strdup("?"));
	while (str[*start + len] && is_variable_char(str[*start + len]))
		len++;
	if (len == 0)
		return (ft_strdup("$"));
	variable = ft_substr(str, *start, len);
	*start += len;
	return (variable);
}
