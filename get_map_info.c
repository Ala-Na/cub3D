/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 17:35:08 by fmonbeig          #+#    #+#             */
/*   Updated: 2022/01/14 18:10:26 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_map_width(char *line, t_data *data)
{
	static int	count = 0;
	int			i;

	i = 0;
	count++;
	if (count > 6)
	{
		while (line[i])
			i++;
		if (i > data->map_info->width)
			data->map_info->width = i;
	}
}

static void	file_is_a_directory(char *file, t_data *data)
{
	int	fd;

	fd = open(file, O_WRONLY);
	if (fd < 0)
	{
		close(fd);
		ft_error(ERROR_DIRECTORY, data);
	}
	close(fd);
}

static void	no_map(t_data *data)
{
	if (data->map_info->width <= 0
		|| data->map_info->height <= 0)
		ft_error(ERROR_MAP_IS_NOT_REAL, data);
}

void	get_info_map(char *file, t_data *data)
{
	int		fd;
	int		ret;
	char	*line;

	ret = 1;
	file_is_a_directory(file, data);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_error(NULL, data);
	while (ret)
	{
		ret = get_next_line(fd, &line, 0);
		if (ret == -1)
			ft_error_during_gnl(ERROR_GNL, fd, line, data);
		if (line && line[0])
		{
			data->map_info->height += 1;
			get_map_width(line, data);
		}
		free(line);
		line = NULL;
	}
	data->map_info->height -= 6;
	no_map(data);
	close(fd);
}
