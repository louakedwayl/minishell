/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:59:38 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/22 22:24:28 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/minishell.h"

static int	handler_redirection(int save[2], t_cmd *cmd)
{
	save[STDIN_FILENO] = dup(STDIN_FILENO);
	save[STDOUT_FILENO] = dup(STDOUT_FILENO);
	if (ft_open_files(cmd) == EXIT_FAILURE)
	{
		close(save[STDIN_FILENO]);
		close(save[STDOUT_FILENO]);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static void	handler_restore_and_close(int save[2])
{
	dup2(save[STDIN_FILENO], STDIN_FILENO);
	dup2(save[STDOUT_FILENO], STDOUT_FILENO);
	close(save[STDIN_FILENO]);
	close(save[STDOUT_FILENO]);
}

static void	handler_echo(t_cmd *cmd)
{
	if (has_echo_option(cmd->arg))
		ft_echo(1, cmd->arg, STDOUT_FILENO);
	else
		ft_echo(0, cmd->arg, STDOUT_FILENO);
}

int	exec_builtins(t_cmd *cmd)
{
	int	save[2];

	if (handler_redirection(save, cmd))
		return (EXIT_FAILURE);
	if (!ft_strncmp (cmd->arg[0], "pwd", 4))
		ft_pwd(STDOUT_FILENO);
	else if (!ft_strncmp (cmd->arg[0], "echo", 4))
		handler_echo(cmd);
	else if (!ft_strncmp (cmd->arg[0], "env", 4))
		ft_env(STDOUT_FILENO);
	else if (!ft_strncmp (cmd->arg[0], "exit", 5))
	{
		close(save[STDIN_FILENO]);
		close(save[STDOUT_FILENO]);
		ft_exit(cmd->arg, get_data()->status);
	}
	else if (!ft_strncmp (cmd->arg[0], "unset", 6))
		ft_unset(cmd->arg);
	else if (!ft_strncmp (cmd->arg[0], "cd", 3))
		ft_cd(cmd->arg);
	else if (!ft_strncmp (cmd->arg[0], "export", 7))
		ft_export(&cmd->arg[1]);
	handler_restore_and_close(save);
	return (EXIT_SUCCESS);
}
