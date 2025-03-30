/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:18:28 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/25 18:59:11 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/minishell.h"

static void	handler_error(char **args, int i)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("export: '", STDERR_FILENO);
	ft_putstr_fd(args[i], STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

static void	handler_setenv_error(void)
{
	clear_all();
	printf ("ft_free ce qui faut ft_free");
	exit (EXIT_SUCCESS);
}

int	ft_export(char **args)
{
	t_data	*data;
	int		i;
	char	**env_var;

	i = 0;
	data = get_data();
	while (args[i])
	{
		env_var = split_name_value(args[i]);
		if (ft_is_valid_var(env_var[KEY]))
		{
			if (ft_setenv(env_var[KEY], env_var[VALUE]) == -1)
				handler_setenv_error();
		}
		else
			handler_error(args, i);
		i++;
	}
	data->status = 0;
	return (EXIT_SUCCESS);
}
