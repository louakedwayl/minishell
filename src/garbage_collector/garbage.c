/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 20:17:43 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/25 20:25:30 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include <stdbool.h>
#include <stdlib.h>

void	*ft_malloc(size_t size_to_alloc)
{
	void	*ptr;

	ptr = malloc(size_to_alloc);
	if (ptr == NULL)
		return (NULL);
	if (create_node_garbage(ptr) == -1)
		return (NULL);
	return (ptr);
}

void	soft_clear(void)
{
	t_garbage		*garbage;
	t_garbage_elem	*current;
	t_garbage_elem	*next;
	t_garbage_elem	*prev;

	garbage = get_garbage();
	current = garbage->first;
	while (current)
	{
		prev = current->prev;
		next = current->next;
		if (current->lock == false)
		{
			if (prev == NULL)
				garbage->first = next;
			if (prev)
				prev->next = next;
			if (next)
				next->prev = prev;
			free(current->ptr);
			free(current);
		}
		current = next;
	}
}

void	clear_all(void)
{
	t_garbage		*garbage;
	t_garbage_elem	*current;
	t_garbage_elem	*next;

	garbage = get_garbage();
	current = garbage->first;
	while (current)
	{
		next = current->next;
		free(current->ptr);
		free(current);
		current = next;
	}
	garbage->first = NULL;
}

void	ft_free(void *ptr)
{
	if (is_in_garbage(ptr) == false)
		free(ptr);
	else
		destroy_garbage_node(ptr);
}
