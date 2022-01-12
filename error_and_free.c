/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:43:15 by fmonbeig          #+#    #+#             */
/*   Updated: 2022/01/12 18:09:34 by fmonbeig         ###   ########.fr       */
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

void	ft_error_during_gnl(char *error_message, int fd, char *line, t_data *data)
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

void	ft_error_during_gnl(char *error_message, int fd, char *line, t_data *data)
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

static void	free_int_double_pointer(int numb, int **temp)
{
	int	i;

	i = -1;
	while (++i < numb)
		free(temp[i]);
	free(temp);
	printf("COUCOU\n");
}

void	free_texture(t_data *data)
{
	printf("F = %p\n", data->texture.f_file);
	printf("C = %p\n", data->texture.c_file);
	if (data->texture.temp)
		ft_free_split(data->texture.temp);
	if (data->texture.no_file)
		free(data->texture.no_file);
	if (data->texture.so_file)
		free(data->texture.so_file);
	if (data->texture.we_file)
		free(data->texture.we_file);
	if (data->texture.ea_file)
		free(data->texture.ea_file);
	if (data->texture.f_file)
		free_int_double_pointer(3, data->texture.f_file);
	if (data->texture.c_file)
		free_int_double_pointer(3, data->texture.c_file);
}

void	free_everything(t_data *data)
{
	if (data->map)
		ft_free_split(data->map);
	free_texture(data);
	exit(1);
}
