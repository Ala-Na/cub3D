/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_element.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:06:07 by fmonbeig          #+#    #+#             */
/*   Updated: 2022/01/12 18:12:03 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static void	filled_one_element(char **str, int fd, char *line, t_data *data)
{
	if (*str)
		ft_error_during_gnl(ERROR_ELEMENT_DOUBLON, fd, line, data);
	*str = ft_strdup(suppress_white_space(&line[2]));
	if (!str)
		ft_error_during_gnl(ERROR_MALLOC, fd, line, data);
}

static int	**malloc_colour(int fd, char *line, t_data *data) // TODO : avec un flag on peut savoir qui on malloc
{
	int	i;
	int	**colour;

	i = -1;
	colour = ft_calloc(3, sizeof(int *));
	if (!colour)
		ft_error_during_gnl(ERROR_MALLOC, fd, line, data);
	printf("adrese de colour %p\n", colour);
	while (++i < 3)
		colour[i] = ft_calloc(1, sizeof(int));
	return (colour);
}

static int	**filled_floor_or_ceiling(int fd, char *line, t_data *data) //FIXME trop long
{
	int	i;
	int	**colour; // TODO il faut envoyer ce int **colour pour qu'il se fasse kill ou ne plus l'utiliser

	i = -1;
	colour = malloc_colour(fd, line, data);
	data->texture.temp = ft_split(&line[2], ',');
	if (!data->texture.temp)
		ft_error_during_gnl(ERROR_MALLOC, fd, line, data);
	while (data->texture.temp[++i])
	{
		if (!ft_isnumber(data->texture.temp[i]))
			ft_error_during_gnl(ERROR_COLOUR_WRONG_ELE, fd, line, data);
		if (i == 3)
			ft_error_during_gnl(ERROR_COLOUR_TOO_MANY, fd, line, data);
	}
	if (i != 3)
		ft_error_during_gnl(ERROR_NO_COLOUR, fd, line, data);
	i = -1;
	while (++i < 3)
		*colour[i] = ft_atoi(data->texture.temp[i]);
	i = -1;
	while (++i < 3)
		if (*colour[i] < 0 || *colour[i] > 255)
			ft_error_during_gnl(ERROR_COLOUR_NOT_RGB, fd, line, data);
	ft_free_split(data->texture.temp);
	data->texture.temp = NULL;
	return (colour);
}

void get_element(int fd, char *line, t_data *data) //FIXME trop long
{
	if (line)
	{
		if (!ft_strncmp(line, "NO ", 3))
			filled_one_element(&data->texture.no_file, fd, line, data);
		else if (!ft_strncmp(line, "SO ", 3))
			filled_one_element(&data->texture.so_file, fd, line, data);
		else if (!ft_strncmp(line, "WE ", 3))
			filled_one_element(&data->texture.we_file, fd, line, data);
		else if (!ft_strncmp(line, "EA ", 3))
			filled_one_element(&data->texture.ea_file, fd, line, data);
		else if (!ft_strncmp(line, "F ", 2))
		{
			if (data->texture.f_file)
				ft_error_during_gnl(ERROR_ELEMENT_DOUBLON, fd, line, data);
			data->texture.f_file = filled_floor_or_ceiling(fd, line, data);
		}
		else if (!ft_strncmp(line, "C ", 2))
		{
			if (data->texture.c_file)
				ft_error_during_gnl(ERROR_ELEMENT_DOUBLON, fd, line, data);
			data->texture.c_file = filled_floor_or_ceiling(fd, line, data); //TODO passer un flag
		}
		else if (!ft_strncmp(line, "\0", 1))
			return ;
		else
		{
			if (!all_filled_up(data))
				ft_error_during_gnl(ERROR_ELEMENT, fd, line, data);
		}
	}
}
