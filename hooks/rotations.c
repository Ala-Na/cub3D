/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 14:18:29 by anadege           #+#    #+#             */
/*   Updated: 2022/01/13 20:55:34 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    rotate(int keycode, t_data *data)
{
    t_img   *new_img;

    if (keycode == ROTATE_RIGHT)
        rotate_right(data->player);
    else
        rotate_left(data->player);
    new_img = generate_new_empty_image(data, data->screen_width, data->screen_height);
    if (new_img->img == NULL)
    {
        return; //TODO Error management
    }
    raycasting_algorithm(data, new_img);
    mlx_put_image_to_window(data->mlx, data->win, new_img->img, 0, 0);
    //mlx_destroy_image(data->mlx, data->img->img);
    //free(data->img);
    data->img = new_img;
}

void    rotate_right(t_player *player)
{
    double  old_dir_x;
    double  old_cam_plane_x;

    old_dir_x = player->dir.x;
    old_cam_plane_x = player->cam_plane.x;
    player->dir.x = player->dir.x * cos(ROTATE) - player->dir.y * sin(ROTATE);
    player->dir.y = old_dir_x * sin(ROTATE) + player->dir.y * cos(ROTATE);
    player->cam_plane.x = player->cam_plane.x * cos(ROTATE) - player->cam_plane.y * sin(ROTATE); 
    player->cam_plane.y = old_cam_plane_x * sin(ROTATE) + player->cam_plane.y * cos(ROTATE);
}

void    rotate_left(t_player *player)
{
    double  old_dir_x;
    double  old_cam_plane_x;

    old_dir_x = player->dir.x;
    old_cam_plane_x = player->cam_plane.x;
    player->dir.x = player->dir.x * cos(-ROTATE) - player->dir.y * sin(-ROTATE);
    player->dir.y = old_dir_x * sin(-ROTATE) + player->dir.y * cos(-ROTATE);
    player->cam_plane.x = player->cam_plane.x * cos(-ROTATE) - player->cam_plane.y * sin(-ROTATE); 
    player->cam_plane.y = old_cam_plane_x * sin(-ROTATE) + player->cam_plane.y * cos(-ROTATE);
}