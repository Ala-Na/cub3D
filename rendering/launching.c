/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launching.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 14:29:57 by anadege           #+#    #+#             */
/*   Updated: 2022/01/13 15:41:20 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    convert_floor_and_ceiling_colors(t_data *data)
{
    int **fl;
    int **ce;

    fl = data->texture->f_file;
    ce = data->texture->c_file;
    data->texture->f_value = convert_RGB_to_int(0, *fl[0], *fl[1], *fl[2]);
    data->texture->c_value = convert_RGB_to_int(0, *ce[0], *ce[1], *ce[2]);    
}

void    launch_engine(t_data *data)
{
    t_img   img;

    convert_floor_and_ceiling_colors(data);
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
    data->texture->f_value = 
    img = generate_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (img.img == NULL)
    {
        printf("ERROR EXIT\n");
        return; //TODO ADD ERROR, FREE MLX AND WIN
    }
    data->img = &img;
    raycasting_algorithm(data, &img, player, map);
    mlx_put_image_to_window(data->mlx, data->win, img.img, 0, 0);
    set_hooks(data);
    mlx_loop(data->mlx); 
}
