/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:09:28 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/22 19:22:20 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_name_var(char *string)
{
	int	i;

	i = 0;
	while (string[i] && string[i] != '=')
	{
		if (!(ft_isalnum(string[i]) || string[i] == '_'))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	ft_check_first_char(char *string)
{
	if (!string)
		return (EXIT_FAILURE);
	if (ft_isalpha(string[0]) != 0 || string[0] == '_')
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

bool	ft_is_valid_var(char *string)
{
	int	i;

	if (ft_isalpha(string[0]) == 0 && string[0] != '_')
		return (false);
	i = 1;
	while (string[i])
	{
		if (ft_isalnum(string[i]) == 0 && string[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

char	**env_to_2d_array(t_env *env)
{
	char	**dest;
	char	*str;

	dest = NULL;
	while (env)
	{
		if (env->value == NULL)
			str = ft_strdup(env->key);
		else
		{
			str = ft_strjoin(env->key, "=");
			str = ft_re_strjoin(str, env->value);
		}
		add_string_char_2d(&dest, str);
		env = env->next;
	}
	return (dest);
}

void	remove_variable(char *variable)
{
	t_data	*data;
	t_env	*env;

	data = get_data();
	env = data->env;
	while (env)
	{
		if (ft_strcmp(env->key, variable) == 0)
		{
			if (env->prev == NULL)
				data->env = env->next;
			if (env->prev)
				env->prev->next = env->next;
			if (env->next)
				env->next->prev = env->prev;
			ft_free(env->key);
			ft_free(env->value);
			ft_free(env);
			return ;
		}
		env = env->next;
	}
}
