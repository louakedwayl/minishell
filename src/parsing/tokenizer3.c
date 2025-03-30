/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 19:42:09 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/22 19:46:26 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token_node(char *content, t_type type)
{
	t_token	*new;

	new = ft_malloc(sizeof(t_token));
	ft_bzero(new, sizeof(t_token));
	new->content = content;
	new->type = type;
	return (new);
}

bool	is_redirection(t_type type)
{
	if (type == OPERATOR_OUT)
		return (true);
	if (type == OPERATOR_IN)
		return (true);
	if (type == OPERATOR_HEREDOC)
		return (true);
	if (type == OPERATOR_APPEND)
		return (true);
	return (false);
}

void	set_good_type(t_queue *queue)
{
	t_token	*new;

	new = queue->last;
	if (new->prev && is_redirection(new->prev->type) == true)
		new->type = FILES;
	else
	{
		if (new->prev == NULL)
			new->type = CMD;
		else if (new->prev->type == PIPE)
			new->type = CMD;
		else
			new->type = ARG;
	}
}

void	add_to_queue(t_queue *queue, char *content, t_type type)
{
	t_token	*new;

	new = create_token_node(content, type);
	if (queue->first == NULL)
		queue->first = new;
	else
	{
		queue->last->next = new;
		new->prev = queue->last;
	}
	queue->last = new;
	if (type == WORD)
		set_good_type(queue);
}

void	add_operator(t_queue *queue, char *str, int *i)
{
	char	op;
	int		len;
	char	*operator;
	t_type	type;

	op = str[*i];
	len = 0;
	while (str[*i + len] && str[*i + len] == op)
		len++;
	operator = ft_substr(str, *i, len);
	type = affect_type(operator);
	add_to_queue(queue, operator, type);
	*i += len;
}
