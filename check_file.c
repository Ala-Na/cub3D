/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 16:03:42 by fmonbeig          #+#    #+#             */
/*   Updated: 2022/01/13 14:23:12 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


t_bool	all_filled_up(t_data *data)
{
	if (data->texture->no_file
			&& data->texture->so_file
			&& data->texture->we_file
			&& data->texture->ea_file
			&& data->texture->c_file
			&& data->texture->f_file)
				return (1);
	return (0);
}

static void	check_extension(char *file, t_data *data)
{
	int	i;

	i = 0;
	while (file[i])
		i++;
	if (file[--i] != 'b')
		ft_error(ERROR_NAME_MAP,data);
	if (file[--i] != 'u')
		ft_error(ERROR_NAME_MAP,data);
	if (file[--i] != 'c')
		ft_error(ERROR_NAME_MAP,data);
	if (file[--i] != '.')
		ft_error(ERROR_NAME_MAP,data);
	if (ft_strlen(file) <= 4)
		ft_error(ERROR_NAME_MAP,data);
}

void	check_file(char *file, t_data *data)
{
	int		fd;
	int		ret;
	char	*line;

	ret = 1;
	check_extension(file, data);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_error(NULL, data);
	while (ret)
	{
		ret = get_next_line(fd, &line, 0);
		if (ret == -1)
			ft_error_during_gnl(ERROR_GNL, fd, line, data);
		if (line && line[0] == '\0' && data->texture->flag_map == 1)
			ft_error_during_gnl(ERROR_MAP_EMPTY_LINE, fd, line, data);
		if (all_filled_up(data) && line && line[0])
			get_map(fd, line, data);
		get_element(fd, line, data);
		free(line);
		line = NULL;
	}
	close(fd);
}
