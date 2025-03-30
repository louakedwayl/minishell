/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:41:17 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/22 23:19:03 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/minishell.h"
#include <stdio.h>

static void	set_data(t_data	*data, int *status)
{
	data->status = WTERMSIG(*status);
	printf("\n");
	data->status += 128;
}

static void	handler_wait_and_signal2(t_cmd *current)
{
	int		status;
	t_data	*data;

	data = get_data();
	while (current)
	{
		if (waitpid(current->pid, &status, 0) == -1)
		{
			if (current->heredoc_name)
				unlink(current->heredoc_name);
			return ;
		}
		if (current->heredoc_name)
			unlink(current->heredoc_name);
		current = current->next;
	}
	if (WIFEXITED(status))
		data->status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		set_data(data, &status);
	}
	else if (WIFSTOPPED(status))
		data->status = WSTOPSIG(status);
	signal_handler();
}

static void	handler_one_cmd(t_cmd *current)
{
	if ((current->arg) && check_built_in(current->arg[0]))
	{
		exec_builtins(current);
	}
	else
	{
		current->pid = fork();
		if (current->pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			exec_cmd(current);
		}
		handler_wait_and_signal2(current);
	}
}

static void	handler_close_pipe(t_cmd *current)
{
	if (current->next)
		close(current->pipe_fd[1]);
	if (current->prev)
		close(current->prev->pipe_fd[0]);
}

void	ft_exec(t_cmd *cmd)
{
	t_cmd	*current;

	current = cmd;
	set_ignore_signals();
	if (current->next == NULL)
		handler_one_cmd(current);
	else
	{
		while (current)
		{
			ft_create_pipe(current);
			current->pid = fork();
			routine_cmd(current);
			handler_close_pipe(current);
			current = current->next;
		}
		handler_wait_and_signal2(cmd);
	}
}
