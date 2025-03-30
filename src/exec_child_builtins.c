/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child_builtins.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:15:14 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/22 22:25:48 by wlouaked         ###   ########.fr       */
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
	dup2(cmd->out_fd, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}

static void	handler_restore_and_close(int save[2])
{
	dup2(save[STDIN_FILENO], STDIN_FILENO);
	dup2(save[STDOUT_FILENO], STDOUT_FILENO);
	close(save[STDIN_FILENO]);
	close(save[STDOUT_FILENO]);
}

static int	handler_echo(t_cmd *cmd)
{
	if (has_echo_option(cmd->arg))
		return (ft_echo(1, cmd->arg, STDOUT_FILENO));
	else
		return (ft_echo(0, cmd->arg, STDOUT_FILENO));
}

static int	handler_child(t_cmd *cmd, int *save)
{
	if (!ft_strncmp (cmd->arg[0], "pwd", 4))
		return (ft_pwd(STDOUT_FILENO));
	else if (!ft_strncmp (cmd->arg[0], "echo", 4))
		return (handler_echo(cmd));
	else if (!ft_strncmp (cmd->arg[0], "env", 4))
		return (ft_env(STDOUT_FILENO));
	else if (!ft_strncmp (cmd->arg[0], "exit", 5))
	{
		close(save[STDIN_FILENO]);
		close(save[STDOUT_FILENO]);
		return (ft_exit(cmd->arg, 42));
	}
	else if (!ft_strncmp (cmd->arg[0], "unset", 6))
		return (ft_unset(cmd->arg));
	else if (!ft_strncmp (cmd->arg[0], "cd", 3))
		return (ft_cd(cmd->arg));
	else if (!ft_strncmp (cmd->arg[0], "export", 7))
		return (ft_export(&cmd->arg[1]));
	return (1);
}

int	exec_child_builtins(t_cmd *cmd)
{
	int	save[2];
	int	status;

	status = 1;
	if (handler_redirection(save, cmd))
		exit(status);
	handler_restore_and_close(save);
	status = handler_child(cmd, save);
	close_both(cmd->in_fd, cmd->out_fd);
	clear_all();
	exit (status);
}
