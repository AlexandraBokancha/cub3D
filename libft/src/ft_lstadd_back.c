/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:48:30 by dbaladro          #+#    #+#             */
/*   Updated: 2024/08/13 11:17:54 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new_elem)
{
	t_list	*last;

	if (!(*alst))
		*alst = new_elem;
	else
	{
		last = ft_lstlast(*alst);
		last->next = new_elem;
	}
}
