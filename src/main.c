/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 20:03:09 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/26 16:34:56 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/minishell.h"

int	g_flag_signal = 0;

static void	init(int argc, char **argv, t_data	**data, char ***envp)
{
	(void)argc;
	(void)argv;
	ft_set_env(envp);
	rl_event_hook = sig_event;
	*data = get_data();
	(*data)->name = "minishell";
}

static void	handler_parsing(t_cmd	**cmds, t_token	**tokens, char **cmd_line)
{
	*tokens = tokenizer(*cmd_line);
	ft_free(*cmd_line);
	if (*tokens == NULL)
		return ;
	*cmds = parser(*tokens);
}

static void	signal_handler_and_readline(char **cmd_line)
{
	signal_handler();
	*cmd_line = readline("minishell> ");
}

static void	handler_pars_init(t_cmd	**cmds, t_token	**tokens, char	**cmd_line)
{
	*cmds = NULL;
	handler_parsing(cmds, tokens, cmd_line);
}

int	main(int argc, char **argv, char **envp)
{
	char	*cmd_line;
	t_cmd	*cmds;
	t_token	*tokens;
	t_data	*data;

	init(argc, argv, &data, &envp);
	while (1)
	{
		signal_handler_and_readline(&cmd_line);
		if (g_flag_signal != 0)
		{
			set_data_signal(data);
			continue ;
		}
		if (!cmd_line)
		{
			handler_eof();
			break ;
		}
		handler_pars_init(&cmds, &tokens, &cmd_line);
		if (cmds != NULL)
			ft_exec(cmds);
		soft_clear();
	}
	return (rl_clear_history(), EXIT_SUCCESS);
}
