/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 16:03:42 by fmonbeig          #+#    #+#             */
/*   Updated: 2022/01/11 16:25:26 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"


t_bool	all_filled_up(t_data *data)
{
	if (data->texture.no_file
			&& data->texture.so_file
			&& data->texture.we_file
			&& data->texture.ea_file
			&& data->texture.c_file
			&& data->texture.f_file)
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
		get_element(fd, line, data);
		if (all_filled_up(data))
		{
			printf("LINE %s\n", line);
			//printf(" I have everything but the map\n");
		}
			//if (line)
			//get_map()
		// if (line && ret == 1)
		// {
			free(line);
			line = NULL;
	}
}

//TODO fonction get_map, pour la put dans un char ** (a faire apres avec un second gnl)
//Permet d'obtenir des infos sur la taille de la map par exemple

// doit recuperer d'abord les 6 infos essentielles sinon quit
