/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 19:50:26 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/22 19:59:52 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_quotes(char *str)
{
	int		i;
	int		len;
	char	*substr;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			len = len_to_next_char(str, i, str[i]);
			substr = ft_substr(str, i + 1, len - 2);
			substr = ft_re_strjoin(substr, &str[i + len]);
			ft_strcpy(&str[i], substr);
			ft_free(substr);
			i += len - 2;
		}
		else
			i++;
	}
}

void	remove_quotes_on_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i])
	{
		remove_quotes(tab[i]);
		i++;
	}
}

char	*expand_line(char *word)
{
	char	*result;
	char	*dest;
	int		start;

	start = 0;
	result = NULL;
	while (word[start])
	{
		if (word[start] == '"')
			dest = dquote_expand(word, &start);
		else if (word[start] == '\'')
			dest = quote_expand(word, &start);
		else
			dest = normal_expand(word, &start);
		result = ft_re_strjoin(result, dest);
	}
	return (result);
}

char	**expand_word(char *word)
{
	char	*result;
	char	**tab;

	result = expand_line(word);
	tab = split_expand(result);
	remove_quotes_on_tab(tab);
	return (tab);
}

char	**expand(char **args)
{
	char	**dest;
	int		i;

	i = 0;
	dest = NULL;
	if (args == NULL)
		return (NULL);
	while (args[i])
	{
		dest = re_str2djoin(dest, expand_word(args[i]));
		i++;
	}
	return (dest);
}
