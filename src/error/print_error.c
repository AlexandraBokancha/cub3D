/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 11:30:23 by dbaladro          #+#    #+#             */
/*   Updated: 2024/08/14 15:06:04 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Print an error on standard error output 
 *
 * It will print an error under th following format
 * 'cub3D: <called function>: <error desc>\n'
 *
 * @param func The function that raised the error
 * @param error_nbr Error code (errno)
 * */
void	print_error(const char *func, int error_nbr)
{
	int		msg_len;
	char	*error_msg;

	error_msg = strerror(error_nbr);
	write(2, "cub3D: ", 7);
	msg_len = ft_strlen(func);
	write(2, func, msg_len);
	write(2, ": ", 2);
	msg_len = ft_strlen(error_msg);
	write(2, error_msg, msg_len);
	write(2, "\n", 1);
}
