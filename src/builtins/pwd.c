/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:22:30 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/25 19:00:27 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/minishell.h"

//pwd ne retourne que 0

int	ft_pwd(int fd)
{
	t_data	*data;
	char	buff[PATH_MAX];

	data = get_data();
	if (getcwd(buff, PATH_MAX) != NULL)
	{
		ft_putstr_fd(buff, fd);
		ft_putchar_fd('\n', fd);
		data->status = 0;
		return (EXIT_SUCCESS);
	}
	else
	{
		perror("minishell");
		data->status = 1;
		return (EXIT_FAILURE);
	}
}

/*
int main (void)
{
	pwd();
}
*/
