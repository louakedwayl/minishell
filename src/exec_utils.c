/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 22:15:33 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/22 23:19:11 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/minishell.h"

int	ft_create_pipe(t_cmd *cmd)
{
	if (cmd->next)
	{
		if (pipe(cmd->pipe_fd) == -1)
		{
			perror("Error - Unable to create pipe ");
			return (-1);
		}
	}
	return (0);
}

void	routine_cmd(t_cmd *current)
{
	if (current->pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (current->next)
		{
			close(current->pipe_fd[0]);
			dup2(current->pipe_fd[1], STDOUT_FILENO);
			close(current->pipe_fd[1]);
		}
		if (current->prev)
		{
			dup2(current->prev->pipe_fd[0], STDIN_FILENO);
			close(current->prev->pipe_fd[0]);
		}
		if (current->arg && check_built_in(current->arg[0]))
		{
			if ((current->arg))
				exec_child_builtins(current);
		}
		else
			exec_cmd(current);
	}
}
