/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_element.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:06:07 by fmonbeig          #+#    #+#             */
/*   Updated: 2022/01/10 17:22:26 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static char	*suppress_white_space(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (ft_iswhitespace(str[i]))
			continue ;
		break ;
	}
	return (&str[i]);
}

static void	filled_one_element(char *str, int fd, char *line, t_data *data)
{
	if (str)
		ft_error_during_gnl(ERROR_ELEMENT_DOUBLON, fd, line, data);
	str = ft_strdup(suppress_white_space(&line[2]));
	if (!str)
		ft_error_during_gnl(ERROR_MALLOC, fd, line, data);
}

static void	filled_floor_or_ceiling(int **colour, int fd, char *line, t_data *data)
{
	int i;

	i = -1;
	data->texture.temp = ft_split(&line[2], ",");
	if (!data->texture.temp)
		ft_error_during_gnl(ERROR_MALLOC, fd, line, data);
	while (data->texture.temp[++i])
	{
		if (!ft_isnumber(data->texture.temp[i]))
			ft_error_during_gnl(ERROR_COLOUR_WRONG_ELE, fd, line, data);
		if (i == 3)
			ft_error_during_gnl(ERROR_COLOUR_TOO_MANY, fd, line, data);
	}
	i = -1;
	while (i < 3)
		colour[i] = ft_atoi(data->texture.temp[i]);
	i = -1;
	while (i < 3)
		if (colour[i] < 0 || colour[i] > 255)
			ft_error_during_gnl(ERROR_COLOUR_NOT_RGB, fd, line, data);
}

t_bool	all_filled_up(t_data *data)
{
	if (data->texture.no_file
			&& data->texture.so_file
			&& data->texture.we_file
			&& data->texture.ea_file
			&& data->texture.f_file
			&& data->texture.c_file)
		return (1);
	return (0);
}

void get_element(int fd, char *line, t_data *data)
{
	if (line)
	{
		if (!ft_strncmp(line, "NO ", 3))
			filled_one_element(data->texture.no_file, fd, line, data);
		else if (!ft_strncmp(line, "SO ", 3))
			filled_one_element(data->texture.so_file, fd, line, data);
		else if (!ft_strncmp(line, "WE ", 3))
			filled_one_element(data->texture.we_file, fd, line, data);
		else if (!ft_strncmp(line, "EA ", 3))
			filled_one_element(data->texture.ea_file, fd, line, data);
		else if (!ft_strncmp(line, "F ", 2))
			filled_floor_or_ceiling(data->texture.f_file, fd, line, data);
		else if (!ft_strncmp(line, "C ", 2))
			filled_floor_or_ceiling(data->texture.c_file, fd, line, data);
		else
			if (!all_filled_up(data))
				ft_error_during_gnl(ERROR_ELEMENT, fd, line, data);
	}
}
