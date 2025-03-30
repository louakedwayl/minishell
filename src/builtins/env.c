/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:17:31 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/25 18:53:19 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// env ne retourne que 0

#include "../hdr/minishell.h"

int	ft_env(int fd)
{
	t_data	*data;
	int		i;
	char	**envp;

	i = 0;
	data = get_data();
	envp = env_to_2d_array(get_data()->env);
	while (envp[i])
	{
		ft_putstr_fd(envp[i], fd);
		ft_putchar_fd('\n', fd);
		i++;
	}
	data->status = 0;
	return (EXIT_SUCCESS);
}
