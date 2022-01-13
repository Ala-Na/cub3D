/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launching.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 14:29:57 by anadege           #+#    #+#             */
/*   Updated: 2022/01/13 19:24:53 by anadege          ###   ########.fr       */
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
    t_img   *new_img;
    
    printf("LAUNCH %f %f %f %f\n", data->player->pos.x, data->player->pos.y, data->player->dir.x, data->player->dir.y);
    convert_floor_and_ceiling_colors(data);
    mlx_get_screen_size(data->mlx, &(data->screen_width), &(data->screen_height));
    data->win = mlx_new_window(data->mlx, data->screen_height, data->screen_height, "Cub3D");
    new_img = generate_new_empty_image(data, data->screen_height, data->screen_height);
    if (new_img->img == NULL)
    {
        printf("ERROR EXIT\n");
        return; //TODO ADD ERROR, FREE MLX AND WIN
    }
    raycasting_algorithm(data, new_img);
    mlx_put_image_to_window(data->mlx, data->win, new_img->img, 0, 0);
    set_hooks(data);
    mlx_loop(data->mlx);
    free_everything(data); 
}
