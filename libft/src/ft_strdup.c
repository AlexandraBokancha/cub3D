/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandra <alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:49:43 by dbaladro          #+#    #+#             */
/*   Updated: 2024/09/19 20:44:44 by alexandra        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strdup(const char *s)
{
	char	*dup;
	int		i;

	i = 0;
	dup = malloc((ft_strlen(s) + 1) * (sizeof(char)));
	if (!dup)
		return (NULL);
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

// char	*ft_strdup(const char *s)
// {
// 	size_t	s_len;
// 	char	*s_cp;

// 	s_len = ft_strlen(s);
// 	s_cp = (char *)malloc(sizeof(char) * (s_len + 1));
// 	if (s_cp != NULL)
// 	{
// 		*(s_cp + s_len) = 0;
// 		while (s_len-- > 0)
// 			*(s_cp + s_len) = *(s + s_len);
// 		return (s_cp);
// 	}
// 	return (NULL);
// }
