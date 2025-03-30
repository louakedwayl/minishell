/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 20:18:34 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/25 20:18:36 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/minishell.h"

int	is_quoted(char *delimiter)
{
	if (delimiter[0] != '\'')
		return (EXIT_FAILURE);
	if (delimiter[ft_strlen(delimiter) - 1] != '\'')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

// void	expand_word(char *var_value, char **retstring, int *j)
// {
// 	int	l;

// 	l = 0;
// 	while (var_value[l] != '\0')
// 	{
// 		(*retstring)[(*j)++] = var_value[l++];
// 	}
// }

void	extract_var(char **line, char **string, int *i, int *k)
{
	(*i)++;
	*k = 0;
	while ((*line)[*i] != '\0' &&
		(ft_isalnum((*line)[*i]) || (*line)[*i] == '_'))
	{
		(*string)[(*k)++] = (*line)[*i];
		(*i)++;
	}
	(*string)[*k] = '\0';
}

// char	*expand_line(char *line)
// {
// 	char			*retstring;
// 	char			*string;
// 	char			*var_value;
// 	t_counter		counter;

// 	init_counter(&counter);
// 	retstring = ft_calloc(4098, sizeof(char));
// 	string = ft_calloc(1048, sizeof(char));
// 	if (!retstring || !string)
// 		return (NULL);
// 	while (line[counter.i] != '\0')
// 	{
// 		if (line[counter.i] != '$' || line[counter.i + 1] == '\0'
// 			|| !ft_isalnum(line[counter.i + 1]))
// 			retstring[counter.j++] = line[counter.i++];
// 		else
// 		{
// 			extract_var(&line, &string, &counter.i, &counter.k);
// 			var_value = ft_getenv(string);
// 			if (var_value != NULL)
// 				expand_word(var_value, &retstring, &counter.j);
// 		}
// 	}
// 	ft_free(string);
// 	return (retstring);
// }

// char	**handler_expand_heredoc(char *delimiter, char ***data)
// {
// 	char	**retstring;
// 	int		i;

// 	if (!is_quoted(delimiter))
// 		return (*data);
// 	retstring = ft_calloc(how_many_line_in_array(*data) + 1, sizeof (char *));
// 	if (!retstring)
// 		return (NULL);
// 	i = 0;
// 	while ((*data)[i])
// 	{
// 		retstring[i] = expand_line((*data)[i]);
// 		i++;
// 	}
// 	return (retstring);
// }
