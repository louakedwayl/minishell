/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:59:36 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/25 19:04:07 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/minishell.h"

// retourne 0 quand aucune erreur
// retourn 1 quand erreur
// ENORME Probleme if (args[2])
int	ft_cd(char **args)
{
	t_data	*data;

	data = get_data();
	if (args[0] && args[1] && args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		data->status = 1;
		return (EXIT_FAILURE);
	}
	if (args[1] == NULL || ft_strncmp(args[1], "~", 1) == 0)
	{
		if (cd_in_home(args) == EXIT_FAILURE)
		{
			data->status = 1;
			return (EXIT_FAILURE);
		}
	}
	else
	{
		if (cd_towards_path(args) == EXIT_FAILURE)
			return (data->status = 1, (EXIT_FAILURE));
	}
	return (data->status = 0, (EXIT_SUCCESS));
}

int	cd_in_home(char **args)
{
	char	*home;

	home = ft_getenv ("HOME");
	if (!home)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (EXIT_FAILURE);
	}
	if (chdir(home) == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd("cd: ", STDERR_FILENO);
		perror(args[1]);
		return (EXIT_FAILURE);
	}
	if (ft_setenv("OLDPWD", ft_getenv ("PWD")) == -1
		|| ft_setenv("PWD", home) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	cd_towards_path(char **args)
{
	if (chdir(args[1]) == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd("cd: ", STDERR_FILENO);
		perror(args[1]);
		return (EXIT_FAILURE);
	}
	else
	{
		if (ft_setenv("OLDPWD", ft_getenv ("PWD")) == -1)
			return (EXIT_FAILURE);
		if (ft_setenv("PWD", args[1]) == -1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

// int main (void)
// {

// }