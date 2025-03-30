/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 20:17:24 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/25 20:24:59 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_H
# define GARBAGE_H

# include <stdbool.h>
# include <stdlib.h>

# define SET 0
# define GET 1

typedef struct s_garbage_elem
{
	void					*ptr;
	bool					lock;
	struct s_garbage_elem	*next;
	struct s_garbage_elem	*prev;
}							t_garbage_elem;

typedef struct s_garbage
{
	struct s_garbage_elem	*first;
}							t_garbage;

// Functions to use
void						ft_free(void *ptr);
void						*ft_malloc(size_t size_to_alloc);
void						lock(void *ptr);
void						unlock(void *ptr);
void						soft_clear(void);
void						clear_all(void);

// Utils
int							create_node_garbage(void *ptr);
t_garbage					*get_garbage(void);
bool						is_in_garbage(void *ptr);
void						destroy_garbage_node(void *ptr);

#endif