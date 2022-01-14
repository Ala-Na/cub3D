/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 17:35:08 by fmonbeig          #+#    #+#             */
/*   Updated: 2022/01/14 18:12:38 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	malloc_map(int fd, char *line, t_data *data)
{
	int	i;

	i = -1;
	if (!data->map)
	{
		data->map = ft_calloc(data->map_info->height + 1, sizeof(char *));
		if (!data->map)
			ft_error_during_gnl(ERROR_MALLOC, fd, line, data);
		while (++i < data->map_info->height)
			data->map[i] = ft_calloc(data->map_info->width + 1, sizeof(char));
		data->map[i] = 0;
	}
}

void	get_map(int fd, char *line, t_data *data)
{
	static int	i = 0;
	int			j;

	data->texture->flag_map = 1;
	j = -1;
	malloc_map(fd, line, data);
	while (line[++j])
		data->map[i][j] = line[j];
	data->map[i][j] = '\0';
	i++;
}
