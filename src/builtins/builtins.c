/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:27:44 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/03 16:30:09 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/minishell.h"

bool	has_echo_option(char **arg)
{
	size_t	i;

	if (arg[1] == NULL)
		return (false);
	if (arg[1][0] == '-')
	{
		i = 1;
		while (arg[1][i] != '\0')
		{
			if (arg[1][i] != 'n')
				return (false);
			++i;
		}
		if (i > 1)
			return (true);
	}
	return (false);
}

int	check_built_in(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp(cmd, "export", 7))
		return (1);
	else if (!ft_strncmp(cmd, "env", 4))
		return (1);
	else if (!ft_strncmp(cmd, "cd", 3))
		return (1);
	else if (!ft_strncmp(cmd, "pwd", 4))
		return (1);
	else if (!ft_strncmp(cmd, "echo", 5))
		return (1);
	else if (!ft_strncmp(cmd, "exit", 5))
		return (1);
	else if (!ft_strncmp(cmd, "unset", 6))
		return (1);
	return (0);
}
