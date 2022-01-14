/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 12:03:14 by fmonbeig          #+#    #+#             */
/*   Updated: 2022/01/14 18:12:16 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_img_with_more_data(t_data *data)
{
	data->texture->no.addr = mlx_get_data_addr(data->texture->no.img,
			&data->texture->no.bits_per_pixel,
			&data->texture->no.line_length, &data->texture->no.endian);
	data->texture->so.addr = mlx_get_data_addr(data->texture->so.img,
			&data->texture->so.bits_per_pixel,
			&data->texture->so.line_length, &data->texture->so.endian);
	data->texture->ea.addr = mlx_get_data_addr(data->texture->ea.img,
			&data->texture->ea.bits_per_pixel,
			&data->texture->ea.line_length, &data->texture->ea.endian);
	data->texture->we.addr = mlx_get_data_addr(data->texture->we.img,
			&data->texture->we.bits_per_pixel,
			&data->texture->we.line_length, &data->texture->we.endian);
	data->texture->no.mlx = NULL;
	data->texture->so.mlx = NULL;
	data->texture->we.mlx = NULL;
	data->texture->ea.mlx = NULL;
}

void	init_img(t_data *data)
{
	data->texture->no.img = mlx_xpm_file_to_image(data->mlx,
			data->texture->no_file,
			&data->texture->no.width,
			&data->texture->no.height);
	data->texture->so.img = mlx_xpm_file_to_image(data->mlx,
			data->texture->so_file,
			&data->texture->so.width,
			&data->texture->so.height);
	data->texture->ea.img = mlx_xpm_file_to_image(data->mlx,
			data->texture->ea_file,
			&data->texture->ea.width,
			&data->texture->ea.height);
	data->texture->we.img = mlx_xpm_file_to_image(data->mlx,
			data->texture->we_file,
			&data->texture->we.width,
			&data->texture->we.height);
	if (!data->texture->no.img || !data->texture->so.img
		|| !data->texture->ea.img
		|| !data->texture->we.img)
		ft_error(ERROR_IMG, data);
	init_img_with_more_data(data);
}
