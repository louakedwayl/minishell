/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 20:03:40 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/26 16:35:03 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/minishell.h"

t_data	*get_data(void)
{
	static t_data	data;

	return (&data);
}

void	unlink_heredoc(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp->prev)
		tmp = tmp->prev;
	while (tmp)
	{
		unlink(cmd->heredoc_name);
		tmp = tmp->next;
	}
}

void	handler_eof(void)
{
	clear_all();
	printf ("exit\n");
}
