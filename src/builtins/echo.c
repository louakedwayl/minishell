/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 19:18:49 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/25 19:11:40 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/minishell.h"

// echo ne retourne que 0

int	ft_echo(int option, char **string, int fd)
{
	t_data	*data;
	int		i;

	i = 1;
	data = get_data();
	if (option == 1)
		i++;
	while (string[i])
	{
		ft_putstr_fd(string[i], fd);
		i++;
		if (string[i])
			ft_putstr_fd(" ", fd);
	}
	if (option == 0)
		ft_putchar_fd('\n', fd);
	return (data->status = 0, (EXIT_SUCCESS));
}

/*
int main (void)
{
	echo(0, "chaine de caractere.");
}
*/