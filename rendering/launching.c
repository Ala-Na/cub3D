/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launching.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 14:29:57 by anadege           #+#    #+#             */
/*   Updated: 2022/01/17 11:05:19 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
 ** Convert RGB code for floor and ceiling as a int** to an unsigned int color.
 */
void	convert_floor_and_ceiling_colors(t_data *data)
{
	int	**fl;
	int	**ce;

	fl = data->texture->f_file;
	ce = data->texture->c_file;
	data->texture->f_value = convert_rgb_to_int(0, *fl[0], *fl[1], *fl[2]);
	data->texture->c_value = convert_rgb_to_int(0, *ce[0], *ce[1], *ce[2]);
}

/*
 ** When launching the engine, we convert the NSWE letter corresponding to
 ** player's direction to a '0' (empty case).
 */
void	modify_map(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->map && data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
			if (ft_strchr("NSWE", data->map[i][j]) != 0)
				data->map[i][j] = '0';
	}
}

/*
 ** FUnction to generate window and start raycasting
 */
void	launch_engine(t_data *data)
{
	t_img	*new_img;

	convert_floor_and_ceiling_colors(data);
	modify_map(data);
	mlx_get_screen_size(data->mlx, &(data->screen_width),
		&(data->screen_height));
	data->win = mlx_new_window(data->mlx, data->screen_width,
			data->screen_height, "Cub3D");
	if (data->win == NULL)
		ft_error(ERROR_WINDOW, data);
	new_img = generate_new_empty_image(data, data->screen_width,
			data->screen_height);
	data->img = new_img;
	raycasting_algorithm(data, new_img);
	mlx_put_image_to_window(data->mlx, data->win, new_img->img, 0, 0);
	set_hooks(data);
	mlx_loop(data->mlx);
	free_everything(data);
}
