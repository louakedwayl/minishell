/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_signal2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:54:35 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/20 21:55:42 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/minishell.h"

void	set_ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal (SIGQUIT, SIG_IGN);
	signal (SIGTSTP, SIG_IGN);
}

void	sigquit_handler(int signum)
{
	ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	(void)signum;
	rl_done = 1;
	return ;
}

void	sigint2_handler(int signum)
{
	(void)signum;
	printf ("\n");
	rl_done = 1;
}

void	set_cmd_signals(void)
{
	signal (SIGINT, sigint2_handler);
	signal (SIGQUIT, sigquit_handler);
	signal (SIGTSTP, SIG_IGN);
}
