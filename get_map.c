/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 17:35:08 by fmonbeig          #+#    #+#             */
/*   Updated: 2022/01/12 17:05:09 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Map limit = MAP_LIMIT * MAP_LIMIT
// la map sera rempli de \0

static void	get_temp_width(char *line, t_data *data)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	if (i > data->map_info.temp_w)
		data->map_info.temp_w = i;
}

void	get_info_map(char *file, t_data *data)
{
	int		fd;
	int		ret;
	char	*line;

	ret = 1;
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
			data->map_info.temp_h += 1;
			get_temp_width(line, data);
		}
		free(line);
		line = NULL;
	}
	data->map_info.temp_h -= 6;
	close(fd);
}

static void	malloc_map(int fd, char *line, t_data *data) // possibilité de calculer avant la taille potentiel de la map
{
	int	i;

	i = -1;
	if (!data->map)
	{
		data->map = ft_calloc(data->map_info.temp_h + 1, sizeof(char *));
		if (!data->map)
			ft_error_during_gnl(ERROR_MALLOC, fd, line, data);
		while (++i < data->map_info.temp_h)
			data->map[i] = ft_calloc(data->map_info.temp_w + 1, sizeof(char));
		data->map[i] = 0;
	}
}

void	get_map(int fd, char *line, t_data *data)
{
	static int	i = 0;
	int			j;

	data->texture.flag_map = 1;
	j = -1;
	malloc_map(fd, line, data);
	while(line[++j])
		data->map[i][j] = line[j];
	data->map[i][j] = '\0';
	i++;
	//avec les /0 on peut faire un algo qui test chaque point de la map pour savoir si elle est ouverte ou fermé // le faire apres les tests preliminaires
	// tester si la map est bien fermé
	// recupérer la position du joueur et son orientation
}