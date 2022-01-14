/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:45:36 by fmonbeig          #+#    #+#             */
/*   Updated: 2022/01/14 18:14:15 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_parsing(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	printf("NO = %s\n", data->texture->no_file);
	printf("SO = %s\n", data->texture->so_file);
	printf("EA = %s\n", data->texture->ea_file);
	printf("WE = %s\n", data->texture->we_file);
	printf("NO = %s\n\n", data->texture->no_file);
	printf("F = %d,%d,%d\n", *data->texture->f_file[0],
		*data->texture->f_file[1],
		*data->texture->f_file[2]);
	printf("C = %d,%d,%d\n\n", *data->texture->c_file[0],
		*data->texture->c_file[1],
		*data->texture->c_file[2]);
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
			printf("%c", data->map[i][j]);
		printf("\n");
	}
	printf("map width = %d\n", data->map_info->width);
	printf("map height = %d\n", data->map_info->height);
}
