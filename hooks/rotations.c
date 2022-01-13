/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 14:18:29 by anadege           #+#    #+#             */
/*   Updated: 2022/01/13 16:00:56 by anadege          ###   ########.fr       */
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
    raycasting_algorithm(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
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