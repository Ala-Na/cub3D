/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colour _utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 12:01:18 by fmonbeig          #+#    #+#             */
/*   Updated: 2022/01/14 17:33:27 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_doublon_c_file(int fd, char *line, t_data *data)
{
	if (data->texture->c_file)
		ft_error_during_gnl(ERROR_ELEMENT_DOUBLON, fd, line, data);
}

void	error_doublon_f_file(int fd, char *line, t_data *data)
{
	if (data->texture->f_file)
		ft_error_during_gnl(ERROR_ELEMENT_DOUBLON, fd, line, data);
}

void	error_no_colour(int fd, char *line, t_data *data, int i)
{
	if (i != 3)
		ft_error_during_gnl(ERROR_NO_COLOUR, fd, line, data);
}
