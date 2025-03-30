/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:44:27 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/25 19:52:03 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/minishell.h"
#include "libft.h"

static void	error_eof_h(void)
{
	ft_putstr_fd("minishell: warning: here-document delimited ", STDERR_FILENO);
	ft_putstr_fd("by end-of-file (wanted delimitor)\n", STDERR_FILENO);
}

int	create_heredoc(t_files *file)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc> ");
		if (g_flag_signal != 0)
			return (ft_free(line), set_data_signal(get_data()), EXIT_FAILURE);
		if (line == NULL)
			return (error_eof_h(), EXIT_SUCCESS);
		if (ft_strcmp(line, file->path) == 0)
			return (ft_free(line), EXIT_SUCCESS);
		if (file->remove_quotes == true)
			add_string_char_2d(&file->heredoc, ft_strdup(line));
		else
			add_string_char_2d(&file->heredoc, expand_str(line));
		ft_free(line);
	}
	return (EXIT_SUCCESS);
}
