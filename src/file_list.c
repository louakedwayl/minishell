/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:24:56 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/22 18:21:21 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/minishell.h"

int	handler_heredoc_operator(t_files *file)
{
	int	fd[2];
	int	i;

	i = 0;
	if (pipe(fd) == -1)
	{
		return (EXIT_FAILURE);
	}
	while (file->heredoc && file->heredoc[i])
	{
		ft_putendl_fd(file->heredoc[i], fd[1]);
		i++;
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	return (EXIT_SUCCESS);
}

int	handler_in_operator(t_files *file)
{
	int	infile;

	if (file->mode == OPERATOR_IN)
	{
		infile = open (file->path, O_RDONLY);
		if (infile == -1)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			perror(file->path);
			return (EXIT_FAILURE);
		}
		dup2(infile, STDIN_FILENO);
		close(infile);
	}
	return (EXIT_SUCCESS);
}

int	handler_out_operator(t_files *file)
{
	int	outfile;

	if (file->mode == OPERATOR_OUT)
		outfile = open (file->path,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file->mode == OPERATOR_APPEND)
		outfile = open (file->path,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (outfile == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(file->path);
		return (EXIT_FAILURE);
	}
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	return (EXIT_SUCCESS);
}

int	ft_open_files(t_cmd *cmd)
{
	t_files	*current_file;

	current_file = cmd->files;
	while (current_file)
	{
		if (current_file->mode == OPERATOR_IN)
			if (handler_in_operator(current_file) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		if (current_file->mode == OPERATOR_HEREDOC)
			if (handler_heredoc_operator(current_file) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		if (current_file->mode == OPERATOR_APPEND
			|| current_file->mode == OPERATOR_OUT)
			if (handler_out_operator(current_file) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		current_file = current_file->next;
	}
	return (EXIT_SUCCESS);
}

void	lst_file_add_back(t_files **file_table, t_files *new)
{
	t_files	*tmp;

	tmp = *file_table;
	if (tmp == NULL)
		*file_table = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}
