/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_re_strjoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 23:25:29 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/25 20:30:30 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_re_strdup(const char *src)
{
	char	*str;

	str = ft_strdup(src);
	ft_free((void *)src);
	return (str);
}

char	*ft_re_strjoin(const char *s1, const char *s2)
{
	size_t	len;
	char	*retstring;

	if (s1 == NULL && s2 != NULL)
		return (ft_strdup(s2));
	if (s1 != NULL && s2 == NULL)
		return (ft_re_strdup(s1));
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	retstring = ft_malloc(sizeof(char) * (len + 1));
	if (!retstring)
		return (NULL);
	ft_strlcpy(retstring, s1, ft_strlen(s1) + 1);
	ft_strlcat(retstring, s2, len + 1);
	ft_free((void *)s1);
	return (retstring);
}
