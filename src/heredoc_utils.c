/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 18:34:22 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/20 18:50:20 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/minishell.h"

int	create_h_files(t_cmd *current, t_files *file_list, int i)
{
	char	*tmp;
	char	*index;

	if (file_list->mode == OPERATOR_HEREDOC)
	{
		tmp = ft_strjoin("._hd", file_list->path);
		index = ft_itoa(i);
		current->heredoc_name = ft_strjoin(tmp, index);
		current->heredoc_read = open(current->heredoc_name, O_CREAT
				| O_RDONLY | O_TRUNC, 0755);
		current->heredoc_write = open(current->heredoc_name, O_CREAT
				| O_WRONLY | O_TRUNC, 0755);
		i++;
		ft_free (tmp);
		ft_free (index);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

void	handler_create_h_files(t_cmd *cmd)
{
	int		i;
	t_cmd	*current;
	t_files	*file_list;

	i = 0;
	current = cmd;
	while (current)
	{
		file_list = current->files;
		while (file_list)
		{
			if (!create_h_files(current, file_list, i))
				break ;
			file_list = file_list->next;
		}
		i++;
		current = current->next;
	}
}

int	if_is_last_heredoc(t_files *lst)
{
	t_files	*current;

	current = lst;
	if (current)
		current = current->next;
	while (current)
	{
		if (current->mode == OPERATOR_HEREDOC)
		{
			return (EXIT_FAILURE);
		}
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

int	handler_wait_and_signal(int pid)
{
	int	exit_status;
	int	exit_code;

	signal_handler();
	waitpid(pid, &exit_code, 0);
	if (WIFEXITED(exit_code))
	{
		exit_status = WEXITSTATUS(exit_code);
		if (exit_status == 2)
		{
			printf ("\n");
			return (2);
		}
		if (exit_status == 3)
		{
			return (2);
		}
	}
	return (EXIT_SUCCESS);
}
