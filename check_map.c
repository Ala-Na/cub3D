/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 17:56:19 by fmonbeig          #+#    #+#             */
/*   Updated: 2022/01/13 14:51:31 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	replace_white_space(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->map[++i])
	{
		j = -1;
		while(data->map[i][++j])
			if (data->map[i][j] == ' ')
				data->map[i][j] = '1';
	}
}

static t_bool	correct_element_in_map(char c)
{
	if (c == '1' || c == '0' || c == 'N'
			|| c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

static void	check_first_line(char *line, t_data *data)
{
	int	i;

	i = -1;
	while(line[++i])
		if (line[i] != '1')
			ft_error(ERROR_MAP_NOT_CLOSE, data);
}

static void check_wrong_data_in_map(char *line, t_data *data)
{
	int	i;

	i = -1;
	while(line[++i])
		if (!correct_element_in_map(line[i]))
			ft_error(ERROR_MAP_WRONG_ELE, data);
}

static void	print_parsing(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	printf("NO = %s\n", data->texture->no_file);
	printf("SO = %s\n", data->texture->so_file);
	printf("EA = %s\n", data->texture->ea_file);
	printf("WE = %s\n", data->texture->we_file);
	printf("NO = %s\n\n", data->texture->no_file);
	printf("F = %d,%d,%d\n", *data->texture->f_file[0], *data->texture->f_file[1], *data->texture->f_file[2]);
	printf("C = %d,%d,%d\n\n", *data->texture->c_file[0],*data->texture->c_file[1], *data->texture->c_file[2]);
	while (data->map[++i])
	{
		j = -1;
		while(data->map[i][++j])
			printf("%c", data->map[i][j]);
		printf("\n");
	}
	printf("\nplayer height = %f\n", data->player->pos.y );
	printf("player width = %f\n", data->player->pos.x );
	printf("map width = %d\n", data->map_info->width );
	printf("map height = %d\n", data->map_info->height);
}

void	check_map(t_data *data)
{
	int	i;

	i = -1;
	replace_white_space(data);
	while (data->map[++i])
	{
		check_wrong_data_in_map(data->map[i], data);
		if (i == 0)
			check_first_line(data->map[i], data);
		check_one(data->map[i], data);
		get_player_position(i, data);
	}
	check_first_line(data->map[i - 1], data);
	if (data->player->dir.x == 0 && data->player->dir.y == 0)
		ft_error(ERROR_NO_PLAYER, data);
	i = -1;
	while (data->map[++i])
		check_close(i, data);
	print_parsing(data); //NOTA BENE: a supprimer plus tard
}
