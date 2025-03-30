/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:50:09 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/22 19:23:49 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/minishell.h"

char	*ft_getenv(const char *name)
{
	t_data	*data;
	t_env	*env;

	data = get_data();
	env = data->env;
	while (env)
	{
		if (ft_strcmp(env->key, name) == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}

char	*ft_set_var(const char *name, const char *value)
{
	char	*retstring;
	int		len;
	int		i;
	int		j;

	len = ft_strlen(name) + ft_strlen(value);
	retstring = ft_calloc(sizeof(char), len + 2);
	if (!retstring)
		return (NULL);
	i = 0;
	while (name[i])
	{
		retstring[i] = name[i];
		i++;
	}
	j = i;
	i = 0;
	retstring[j++] = '=';
	while (value[i])
	{
		retstring[j] = value[i];
		i++;
		j++;
	}
	return (retstring);
}

void	add_back_env(t_env **env, t_env *to_add)
{
	t_env	*current;

	if (*env == NULL)
		*env = to_add;
	else
	{
		current = *env;
		while (current->next)
			current = current->next;
		to_add->prev = current;
		current->next = to_add;
	}
}

bool	is_in_env(char *key)
{
	t_data	*data;
	t_env	*env;

	data = get_data();
	env = data->env;
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (true);
		env = env->next;
	}
	return (false);
}

void	change_value_env(char *key, char *value)
{
	t_data	*data;
	t_env	*env;

	data = get_data();
	env = data->env;
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			ft_free(env->value);
			env->value = value;
			lock(env->value);
			return ;
		}
		env = env->next;
	}
}
