/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_unlock.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 20:17:33 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/25 20:25:23 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"

void	lock(void *ptr)
{
	t_garbage_elem	*current;
	t_garbage		*garbage;

	garbage = get_garbage();
	current = garbage->first;
	while (current)
	{
		if (current->ptr == ptr)
		{
			current->lock = true;
			return ;
		}
		current = current->next;
	}
}

void	unlock(void *ptr)
{
	t_garbage_elem	*current;
	t_garbage		*garbage;

	garbage = get_garbage();
	current = garbage->first;
	while (current)
	{
		if (current->ptr == ptr)
		{
			current->lock = false;
			return ;
		}
		current = current->next;
	}
}
