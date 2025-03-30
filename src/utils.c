/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 19:18:44 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/21 23:19:48 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	how_many_line_in_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

long long	ft_atol(const char *nptr)
{
	long long	nb;
	int			sign;
	size_t		i;

	nb = 0;
	sign = 1;
	i = 0;
	while (ft_isspace(nptr[i]))
		++i;
	if (nptr[i] == '-')
		sign = -1;
	if (nptr[i] == '+' || nptr[i] == '-')
		++i;
	while (ft_isdigit(nptr[i]))
	{
		nb *= 10;
		nb += nptr[i] - '0';
		++i;
	}
	return (sign * nb);
}

bool	is_long(char *arg)
{
	int		i;
	bool	is_negative;

	i = 0;
	is_negative = false;
	if (arg[i] == '-' || arg[i] == '+')
	{
		if (arg[i] == '-')
			is_negative = true;
		++i;
	}
	while (arg[i + 1] != '\0' && arg[i] == '0')
		++i;
	if (ft_strlen(&arg[i]) < 19)
		return (true);
	if (ft_strlen(&arg[i]) > 19)
		return (false);
	if (is_negative && ft_strncmp(&arg[i], "9223372036854775807", 19) > 0)
		return (false);
	if (!is_negative && ft_strncmp(&arg[i], "9223372036854775807", 19) > 0)
		return (false);
	return (true);
}

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r'
		|| c == '\v' || c == '\f')
		return (1);
	return (0);
}

void	close_both(int fd, int fd2)
{
	close (fd);
	close (fd2);
}
