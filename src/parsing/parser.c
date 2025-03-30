/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 20:18:49 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/25 20:18:51 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>

static void	init(t_files	**file, t_token *current)
{
	*file = ft_calloc(sizeof(t_files), 1);
	(*file)->path = ft_strdup(current->next->content);
	(*file)->mode = current->type;
}

int	add_redirect_cmd(t_cmd *new, t_token *current)
{
	t_files	*file;

	if (current->next == NULL)
		return (error_parsing("newline"));
	if (is_operator_type(current->next->type) == true)
		return (error_parsing(current->next->content));
	init(&file, current);
	if (file->mode == OPERATOR_HEREDOC)
	{
		remove_quotes(file->path);
		if (ft_strcmp(file->path, current->next->content) == 0)
			file->remove_quotes = true;
		if (create_heredoc(file) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else
	{
		file->path = expand_line(file->path);
		if (file->path[0] == '\0')
			return (ambiguous_redirect(current->next->content));
		remove_quotes(file->path);
	}
	ft_free(current->content);
	lst_file_add_back(&new->files, file);
	return (EXIT_SUCCESS);
}

void	set_args_cmd(t_cmd *new, t_token *current)
{
	t_token	*tmp;
	int		i;

	tmp = current;
	i = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == CMD || tmp->type == ARG)
			i++;
		tmp = tmp->next;
	}
	new->arg = ft_malloc(sizeof(char *) * (i + 1));
	tmp = current;
	i = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == CMD || tmp->type == ARG)
		{
			new->arg[i] = tmp->content;
			i++;
		}
		tmp = tmp->next;
	}
	new->arg[i] = NULL;
	new->arg = expand(new->arg);
}

t_cmd	*create_cmd(t_token **current)
{
	t_cmd	*new;
	t_token	*buff;

	buff = *current;
	new = create_cmd_node();
	while (buff && buff->type != PIPE)
	{
		if (is_redirection(buff->type))
		{
			if (add_redirect_cmd(new, buff) == EXIT_FAILURE)
				return (NULL);
			buff = buff->next->next;
		}
		else
		{
			if (buff->type == CMD)
				set_args_cmd(new, buff);
			if (buff->type == NONE)
				return (error_parsing(buff->content), NULL);
			buff = buff->next;
		}
	}
	*current = buff;
	return (new);
}

t_cmd	*parser(t_token *queue)
{
	t_cmd	*cmds;
	t_cmd	*new;

	cmds = NULL;
	while (queue)
	{
		if (queue->type == PIPE)
			return (error_parsing("|"), NULL);
		new = create_cmd(&queue);
		if (new == NULL)
			return (NULL);
		lst_cmd_add_back(&cmds, new);
		if (queue)
		{
			if (queue->next == NULL)
				return (error_parsing("|"), NULL);
			queue = queue->next;
		}
	}
	return (cmds);
}
