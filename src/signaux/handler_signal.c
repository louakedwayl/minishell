/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:14:50 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/22 22:00:10 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/minishell.h"

int	sig_event(void)
{
	return (EXIT_SUCCESS);
}

void	sigint_handler(int signum)
{
	g_flag_signal = 128 + signum;
	rl_done = 1;
}

void	signal_handler(void)
{
	rl_event_hook = sig_event;
	signal(SIGINT, sigint_handler);
	signal (SIGQUIT, SIG_IGN);
	signal (SIGTSTP, SIG_IGN);
}

void	sigint_handler_heredoc(int signum)
{
	(void)signum;
	rl_done = 1;
	clear_all();
	exit (2);
}

void	signal_heredoc_handler(void)
{
	signal(SIGINT, sigint_handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
