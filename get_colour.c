/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colour.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 12:01:18 by fmonbeig          #+#    #+#             */
/*   Updated: 2022/01/13 13:36:42 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	error_doublon_c_file(int fd, char *line, t_data *data)
{
	if (data->texture->c_file)
		ft_error_during_gnl(ERROR_ELEMENT_DOUBLON, fd, line, data);
}

static void	error_doublon_f_file(int fd, char *line, t_data *data)
{
	if (data->texture->f_file)
		ft_error_during_gnl(ERROR_ELEMENT_DOUBLON, fd, line, data);
}

static void	error_no_colour(int fd, char *line, t_data *data, int i)
{
	if (i != 3)
		ft_error_during_gnl(ERROR_NO_COLOUR, fd, line, data);
}

static int **malloc_colour(int fd, char *line, t_data *data, char c)
{
	int	i;

	i = -1;
	if (c == 'c')
	{
		error_doublon_c_file(fd, line, data);
		data->texture->c_file = ft_calloc(3, sizeof(int *));
		if (!data->texture->c_file)
			ft_error_during_gnl(ERROR_MALLOC, fd, line, data);
		while (++i < 3)
			data->texture->c_file[i] = ft_calloc(1, sizeof(int));
		return (data->texture->c_file);
	}
	else if (c == 'f')
	{
		error_doublon_f_file(fd, line, data);
		data->texture->f_file = ft_calloc(3, sizeof(int *));
		if (!data->texture->f_file)
			ft_error_during_gnl(ERROR_MALLOC, fd, line, data);
		while (++i < 3)
			data->texture->f_file[i] = ft_calloc(1, sizeof(int));
		return (data->texture->f_file);
	}
	return (NULL);
}

void	filled_floor_or_ceiling(int fd, char *line, t_data *data, char c)
{
	int	i;
	int	**colour;

	i = -1;
	colour = malloc_colour(fd, line, data, c);
	data->texture->temp = ft_split(&line[2], ',');
	if (!data->texture->temp)
		ft_error_during_gnl(ERROR_MALLOC, fd, line, data);
	while (data->texture->temp[++i])
	{
		if (!ft_isnumber(data->texture->temp[i]))
			ft_error_during_gnl(ERROR_COLOUR_WRONG_ELE, fd, line, data);
		if (i == 3)
			ft_error_during_gnl(ERROR_COLOUR_TOO_MANY, fd, line, data);
	}
	error_no_colour(fd, line, data, i);
	i = -1;
	while (++i < 3)
		*colour[i] = ft_atoi(data->texture->temp[i]);
	i = -1;
	while (++i < 3)
		if (*colour[i] < 0 || *colour[i] > 255)
			ft_error_during_gnl(ERROR_COLOUR_NOT_RGB, fd, line, data);
	ft_free_split(data->texture->temp);
	data->texture->temp = NULL;
}
