/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:45:29 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/25 19:02:03 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char **args)
{
	t_data	*data;
	int		i;

	i = 1;
	data = get_data();
	while (args[i])
	{
		remove_variable(args[i]);
		i++;
	}
	data->status = 0;
	return (EXIT_SUCCESS);
}
