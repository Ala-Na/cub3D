/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 17:56:19 by fmonbeig          #+#    #+#             */
/*   Updated: 2022/01/14 18:08:07 by fmonbeig         ###   ########.fr       */
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
		while (data->map[i][++j])
			if (data->map[i][j] == ' ')
				data->map[i][j] = '1';
	}
}

static bool	correct_element_in_map(char c)
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
	while (line[++i])
		if (line[i] != '1')
			ft_error(ERROR_MAP_NOT_CLOSE, data);
}

static void	check_wrong_data_in_map(char *line, t_data *data)
{
	int	i;

	i = -1;
	while (line[++i])
		if (!correct_element_in_map(line[i]))
			ft_error(ERROR_MAP_WRONG_ELE, data);
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
}
