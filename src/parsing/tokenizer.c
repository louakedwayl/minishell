/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 20:19:20 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/25 20:19:22 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_spaces(char *str, int *i)
{
	while (str[*i] && ft_isspace(str[*i]))
		(*i)++;
}

bool	is_operator(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

bool	is_operator_type(t_type type)
{
	if (type == OPERATOR_OUT)
		return (true);
	if (type == OPERATOR_IN)
		return (true);
	if (type == OPERATOR_HEREDOC)
		return (true);
	if (type == OPERATOR_APPEND)
		return (true);
	if (type == PIPE)
		return (true);
	return (false);
}

t_type	affect_type(char *operator)
{
	if (ft_strcmp("<<", operator) == 0)
		return (OPERATOR_HEREDOC);
	if (ft_strcmp("<", operator) == 0)
		return (OPERATOR_IN);
	if (ft_strcmp(">", operator) == 0)
		return (OPERATOR_OUT);
	if (ft_strcmp(">>", operator) == 0)
		return (OPERATOR_APPEND);
	if (ft_strcmp("|", operator) == 0)
		return (PIPE);
	return (NONE);
}
