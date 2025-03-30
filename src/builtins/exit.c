/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 15:43:48 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/25 18:11:58 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	numeric_argument_required_error(char *arg)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
}

static int	ft_invalid_numeric_arg(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (EXIT_SUCCESS);
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			numeric_argument_required_error(arg);
			return (EXIT_FAILURE);
		}
		i++;
	}
	if (is_long(arg) == false)
	{
		numeric_argument_required_error(arg);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_exit(char **arg, int last_status)
{
	int	exit_code;

	exit_code = 0;
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (arg[1] && ft_invalid_numeric_arg(arg[1]))
	{
		clear_all();
		exit (2);
	}
	if (arg[0] && arg[1] && arg[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	if (!arg[1])
	{
		clear_all();
		exit (last_status);
	}
	exit_code = ft_atol(arg[1]) % 256;
	rl_clear_history();
	clear_all();
	exit (exit_code);
}
