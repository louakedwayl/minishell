/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_tokenise.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 20:19:03 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/26 16:27:12 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_quote_close(t_data *data, char *str, int *i)
{
	char	quote;

	quote = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != quote)
		(*i)++;
	if (str[*i] == '\0')
	{
		ft_putstr_fd("minishell: open quotes\n", STDERR_FILENO);
		data->status = 2;
		return (false);
	}
	(*i)++;
	return (true);
}

bool	no_invalid_quotes(t_data *data, char *cmd_line)
{
	int		i;
	bool	check;

	i = 0;
	check = true;
	while (cmd_line && cmd_line[i])
	{
		if (cmd_line[i] == '"' || cmd_line[i] == '\'')
			check = check_quote_close(data, cmd_line, &i);
		else
			i++;
	}
	return (check);
}
