/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:43:15 by fmonbeig          #+#    #+#             */
/*   Updated: 2022/01/10 17:55:24 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/***
 * ft_error : send a error message and exit the program properly.
 * 			if NULL is pass to error_message, we use perror instead.
***/

void	ft_error(char *error_message, t_data *data)
{
	if (!error_message)
		perror("ERROR");
	else
		write(2, error_message, ft_strlen(error_message));
	free_everything(data);
}

void	ft_error_during_gnl(char *error_message, int fd, char *line, t_data *data)
{
	get_next_line(fd, &line, 1);
	free(line);
	if (!error_message)
		perror("ERROR");
	else
		write(2, error_message, ft_strlen(error_message));
	free_everything(data);
}

void	free_texture(t_texture *texture)
{
	if (texture->temp)
		ft_free_split(texture->temp);
	if (texture->no_file)
		free(texture->no_file);
	if (texture->so_file)
		free(texture->so_file);
	if (texture->we_file)
		free(texture->we_file);
	if (texture->ea_file)
		free(texture->ea_file);
}

void	free_everything(t_data *data)
{
	if (data->map)
		ft_free_split(data->map);
	free_texture(&data->texture);
}
