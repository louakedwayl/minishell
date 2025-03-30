/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 19:40:37 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/22 19:47:32 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_separator(char c)
{
	return (is_operator(c) || ft_isspace(c));
}

int	continue_until_find(char *str, int i, char c)
{
	int	len;

	len = 1;
	while (str[i + len] != c)
		len++;
	len++;
	return (len);
}

void	add_word(t_queue *queue, char *str, int *i)
{
	int		len;
	char	*word;

	len = 0;
	while (str[*i + len] && is_separator(str[*i + len]) == false)
	{
		if (str[*i + len] == '"' || str[*i + len] == '\'')
			len += continue_until_find(str, *i + len, str[*i + len]);
		else
			len++;
	}
	word = ft_substr(str, *i, len);
	add_to_queue(queue, word, WORD);
	*i += len;
}

void	create_token(t_queue *queue, char *str, int *i)
{
	if (is_operator(str[*i]) == true)
		add_operator(queue, str, i);
	else
		add_word(queue, str, i);
}

t_token	*tokenizer(char *cmd_line)
{
	t_queue	queue;
	t_data	*data;
	int		i;

	data = get_data();
	ft_bzero(&queue, sizeof(t_queue));
	if (no_invalid_quotes(data, cmd_line) == false)
		return (NULL);
	add_history(cmd_line);
	i = 0;
	while (cmd_line[i])
	{
		skip_spaces(cmd_line, &i);
		if (cmd_line[i])
			create_token(&queue, cmd_line, &i);
	}
	return (queue.first);
}
