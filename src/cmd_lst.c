/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:25:57 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/20 21:54:51 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/minishell.h"

void	lst_cmd_add_back(t_cmd **table_cmd, t_cmd *new)
{
	t_cmd	*tmp;

	if (*table_cmd == NULL)
		*table_cmd = new;
	else
	{
		tmp = *table_cmd;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}

t_cmd	*create_cmd_node(void)
{
	t_cmd	*new_node;

	new_node = ft_malloc (sizeof(t_cmd));
	new_node->path = NULL;
	new_node->arg = NULL;
	new_node->in_fd = 0;
	new_node->out_fd = 1;
	new_node->heredoc_read = -2;
	new_node->files = NULL;
	new_node->heredoc_name = NULL;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}
