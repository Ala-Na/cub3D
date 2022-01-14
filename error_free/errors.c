/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 22:37:43 by anadege           #+#    #+#             */
/*   Updated: 2022/01/14 22:49:27 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/***
 * ft_error : send a error message and exit the program properly.
 * 			if NULL is pass to error_message, we use perror instead.
***/
void	ft_error(char *error_message, t_data *data)
{
	if (!error_message)
		perror("ERROR\n");
	else
		write(2, error_message, ft_strlen(error_message));
	free_everything(data);
}

void	ft_error_during_gnl(char *error_message, int fd,
		char *line, t_data *data)
{
	get_next_line(fd, &line, 1);
	free(line);
	close(fd);
	if (!error_message)
		perror("ERROR\n");
	else
		write(2, error_message, ft_strlen(error_message));
	free_everything(data);
}
