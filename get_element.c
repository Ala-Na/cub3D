/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_element.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:06:07 by fmonbeig          #+#    #+#             */
/*   Updated: 2022/01/13 17:43:28 by anadege          ###   ########.fr       */
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

void	get_element(int fd, char *line, t_data *data)
{
	if (line)
	{
		if (!ft_strncmp(line, "NO ", 3))
			filled_one_element(&data->texture->no_file, fd, line, data);
		else if (!ft_strncmp(line, "SO ", 3))
			filled_one_element(&data->texture->so_file, fd, line, data);
		else if (!ft_strncmp(line, "WE ", 3))
			filled_one_element(&data->texture->we_file, fd, line, data);
		else if (!ft_strncmp(line, "EA ", 3))
			filled_one_element(&data->texture->ea_file, fd, line, data);
		else if (!ft_strncmp(line, "F ", 2))
			filled_floor_or_ceiling(fd, line, data, 'f');
		else if (!ft_strncmp(line, "C ", 2))
			filled_floor_or_ceiling(fd, line, data, 'c');
		else if (!ft_strncmp(line, "\0", 1))
			return ;
		else
		{
			if (!all_filled_up(data))
				ft_error_during_gnl(ERROR_ELEMENT, fd, line, data);
		}
	}
}
