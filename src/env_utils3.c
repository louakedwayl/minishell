/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 19:23:13 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/22 19:26:59 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/minishell.h"

void	add_env_variable(char *key, char *value)
{
	t_env	*new;
	t_data	*data;

	data = get_data();
	new = ft_calloc(sizeof(t_env), 1);
	if (new == NULL)
	{
		return ;
	}
	new->key = key;
	new->value = value;
	lock(new->key);
	lock(new->value);
	lock(new);
	add_back_env(&data->env, new);
}

int	ft_setenv(char *key, char *value)
{
	if (is_in_env(key) == true)
		change_value_env(key, value);
	else
		add_env_variable(key, value);
	return (0);
}
