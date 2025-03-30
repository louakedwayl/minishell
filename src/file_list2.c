/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_list2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 21:02:39 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/20 21:56:06 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/minishell.h"

void	lst_file_add_front(t_files **file_table, t_files *new)
{
	if (new == NULL)
		return ;
	if (*file_table == NULL)
	{
		*file_table = new;
		new->prev = NULL;
		new->next = NULL;
	}
	else
	{
		new->next = *file_table;
		new->prev = NULL;
		(*file_table)->prev = new;
		*file_table = new;
	}
}

void	init_counter(t_counter *counter)
{
	static int	a;
	static int	b;
	static int	c;

	a = 0;
	b = 0;
	c = 0;
	counter->i = a;
	counter->j = b;
	counter->k = c;
}
