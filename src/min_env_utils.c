/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 19:10:02 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/21 23:20:50 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_minimal_env(char ***envp)
{
	char	**new_env;
	char	buff[PATH_MAX];

	getcwd(buff, PATH_MAX);
	new_env = ft_calloc (3, sizeof(char *));
	if (!new_env)
		exit (0);
	new_env[0] = ft_strjoin ("PWD=", buff);
	if (!new_env[0])
	{
		ft_free (new_env);
		exit (EXIT_FAILURE);
	}
	new_env[1] = ft_strdup("SHLVL=1");
	*envp = new_env;
	return (0);
}

void	ft_shlvl(void)
{
	char	*lvl;
	int		tmp;

	lvl = ft_getenv("SHLVL");
	tmp = ft_atoi(lvl);
	if (tmp < 1000)
		tmp++;
	lvl = ft_itoa(tmp);
	if (!lvl)
		exit (EXIT_FAILURE);
	if (ft_setenv(ft_strdup("SHLVL"), lvl) == -1)
	{
		ft_free (lvl);
		exit (EXIT_FAILURE);
	}
}

void	ft_set_env(char ***envp)
{
	if (!(*envp)[0])
	{
		ft_minimal_env(envp);
		ft_export(*envp);
	}
	else
	{
		ft_export(*envp);
		ft_shlvl();
	}
}
