/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 19:51:30 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/22 20:01:33 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*quote_expand(char *str, int *start)
{
	char	*dest;
	int		len;

	len = len_to_next_char(str, *start, '\'');
	dest = ft_substr(str, *start, len);
	if (dest == NULL)
		return (NULL);
	*start += len;
	return (dest);
}

char	*normal_expand(char *to_expand, int *start)
{
	char	*dest;
	int		len;

	len = 0;
	while (to_expand[*start + len] && to_expand[*start + len]
		!= '"' && to_expand[*start + len] != '\'')
		len++;
	dest = ft_substr(to_expand, *start, len);
	if (dest == NULL)
		return (NULL);
	*start += len;
	return (expand_str(dest));
}

char	*expand_variable(char *variable)
{
	t_data	*data;
	t_env	*env;

	data = get_data();
	env = data->env;
	if (ft_strcmp(variable, "$") == 0)
		return (variable);
	if (ft_strcmp(variable, "?") == 0)
		return (ft_free(variable), ft_itoa(data->status));
	while (env)
	{
		if (ft_strcmp(env->key, variable) == 0)
			return (ft_free(variable), ft_strdup(env->value));
		env = env->next;
	}
	ft_free(variable);
	return (ft_strdup(""));
}

char	*expand_str(char *str)
{
	char	*dest;
	char	*variable;
	int		i;

	i = 0;
	dest = NULL;
	while (str[i])
	{
		add_until_dollard(&dest, str, &i);
		if (str[i] == '\0')
			return (dest);
		variable = extract_variable(str, &i);
		variable = expand_variable(variable);
		dest = ft_re_strjoin(dest, variable);
		ft_free(variable);
	}
	return (dest);
}

char	*dquote_expand(char *to_expand, int *start)
{
	char	*dest;
	int		len;

	len = len_to_next_char(to_expand, *start, '"');
	dest = ft_substr(to_expand, *start, len);
	if (dest == NULL)
		return (NULL);
	*start += len;
	return (expand_str(dest));
}
