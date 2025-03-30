/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 23:08:41 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/25 17:59:47 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/minishell.h"
#include <stdio.h>

int	handler_redirection(t_cmd *cmd)
{
	if (ft_open_files(cmd) == EXIT_FAILURE)
	{
		clear_all();
		exit (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (!path)
		return (EXIT_SUCCESS);
	if (stat(path, &path_stat) == -1)
	{
		return (EXIT_SUCCESS);
	}
	if (S_ISDIR(path_stat.st_mode))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void	error_msg(t_cmd *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd->arg[0], STDERR_FILENO);
	ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
}

int	exec_cmd(t_cmd *cmd)
{
	char	**envp;

	handler_redirection(cmd);
	if (cmd->arg == NULL)
		(clear_all(), exit(EXIT_SUCCESS));
	if (is_directory(cmd->arg[0]))
	{
		error_msg(cmd);
		clear_all();
		exit (126);
	}
	if (access(cmd->arg[0], R_OK | X_OK) != -1)
		cmd->path = cmd->arg[0];
	else
		find_cmd_path(cmd, cmd->arg[0]);
	envp = env_to_2d_array(get_data()->env);
	if (execve(cmd->path, cmd->arg, envp) == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(cmd->path);
		clear_all();
		exit (127);
	}
	exit (0);
}
