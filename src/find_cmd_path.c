/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 23:15:45 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/25 19:21:20 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/minishell.h"

char	*ft_add_cmd_name(char *path, char *cmd)
{
	char	*retstring;
	int		i;
	int		j;
	int		pathlen;
	int		cmdlen;

	i = 0;
	j = 0;
	pathlen = ft_strlen (path);
	cmdlen = ft_strlen (cmd);
	retstring = ft_calloc ((cmdlen + pathlen + 2), sizeof(char));
	if (!retstring)
		return (NULL);
	while (i < pathlen)
	{
		retstring[i] = path[i];
		i++;
	}
	retstring[i] = '/';
	i++;
	while (i < (pathlen + cmdlen + 1))
		retstring[i++] = cmd[j++];
	return (retstring);
}

int	search_path(t_cmd *cmd, char ***env_path, char *relative_path)
{
	if (!ft_getenv("PATH"))
	{
		cmd->path = ft_strdup(relative_path);
		if (!cmd->path)
			return (EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	*env_path = ft_split(ft_getenv("PATH"), ':');
	if (!*env_path)
	{
		cmd->path = ft_strdup(relative_path);
		if (!cmd->path)
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}

static int	check_path(t_cmd *cmd,	char **tmp_path, char ***env_path)
{
	if (access(*tmp_path, X_OK) != -1)
	{
		cmd->path = ft_strdup(*tmp_path);
		ft_free (*tmp_path);
		free_tab(*env_path);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	find_cmd_path(t_cmd *cmd, char *relative_path)
{
	char	**env_path;
	char	*tmp_path;
	int		i;

	i = 0;
	if (search_path(cmd, &env_path, relative_path) == EXIT_FAILURE)
		return ;
	while (env_path[i])
	{
		tmp_path = ft_add_cmd_name(env_path[i], relative_path);
		if (!tmp_path)
		{
			free_tab(env_path);
			cmd->path = relative_path;
			return ;
		}
		if (check_path(cmd, &tmp_path, &env_path))
		{
			return ;
		}
		ft_free (tmp_path);
		i++;
	}
	free_tab(env_path);
	cmd->path = ft_strdup(relative_path);
}
