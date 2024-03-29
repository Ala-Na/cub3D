/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:43:15 by fmonbeig          #+#    #+#             */
/*   Updated: 2022/01/14 23:03:42 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_int_double_pointer(int numb, int **temp)
{
	int	i;

	i = -1;
	while (++i < numb)
		free(temp[i]);
	free(temp);
}

void	free_texture(t_data *data)
{
	if (data->texture && data->texture->temp)
		ft_free_split(data->texture->temp);
	if (data->texture && data->texture->no_file)
		free(data->texture->no_file);
	if (data->texture && data->texture->so_file)
		free(data->texture->so_file);
	if (data->texture && data->texture->we_file)
		free(data->texture->we_file);
	if (data->texture && data->texture->ea_file)
		free(data->texture->ea_file);
	if (data->texture && data->texture->f_file)
		free_int_double_pointer(3, data->texture->f_file);
	if (data->texture && data->texture->c_file)
		free_int_double_pointer(3, data->texture->c_file);
}

void	destroy_image(t_data *data)
{
	if (data->texture && data->texture->no.img)
		mlx_destroy_image(data->mlx, data->texture->no.img);
	if (data->texture && data->texture->so.img)
		mlx_destroy_image(data->mlx, data->texture->so.img);
	if (data->texture && data->texture->ea.img)
		mlx_destroy_image(data->mlx, data->texture->ea.img);
	if (data->texture && data->texture->we.img)
		mlx_destroy_image(data->mlx, data->texture->we.img);
}

void	free_everything(t_data *data)
{
	if (data->win)
		mlx_clear_window(data->mlx, data->win);
	destroy_image(data);
	if (data->img && data->img->img)
		mlx_destroy_image(data->mlx, data->img->img);
	if (data->img)
		free(data->img);
	if (data->map)
		ft_free_split(data->map);
	free_texture(data);
	if (data->texture)
		free(data->texture);
	if (data->map_info)
		free(data->map_info);
	if (data->player)
		free(data->player);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	printf("EXIT\n");
	exit(1);
}
