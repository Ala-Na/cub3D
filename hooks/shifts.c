/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shifts.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 12:05:41 by anadege           #+#    #+#             */
/*   Updated: 2022/01/13 17:32:23 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    move(int keycode, t_data *data)
{
    t_img   *old_img;

    if (keycode == MOVE_FOWARD)
        move_foward(data->player, data->map, data->map_info);
    else if (keycode == MOVE_BACKWARD)
        move_backward(data->player, data->map, data->map_info);
    else if (keycode == MOVE_RIGHT)
        move_right(data->player, data->map, data->map_info);
    else
        move_left(data->player, data->map, data->map_info);
    old_img = data->img;
    data->img = generate_new_empty_image(data, data->screen_height, data->screen_height);
    if (data->img == NULL)
    {
        mlx_destroy_image(data->mlx, old_img->img);
        free(old_img);
        return; //TODO Error management
    }
    raycasting_algorithm(data);
    mlx_destroy_image(data->mlx, old_img->img);
    free(old_img);
}

void    move_foward(t_player *player, char **map, t_map *map_info)
{
    int curr_x;
    int curr_y;
    int new_x;
    int new_y;

    new_x = (int)(player->pos.x + player->dir.x * (MOVE + 0.01));
    new_y = (int)(player->pos.y + player->dir.y * (MOVE + 0.01));
    curr_x = (int)(player->pos.x);
    curr_y = (int)(player->pos.y);
    if (new_x < map_info->width && new_x > 0 && map[curr_y][new_x] == '0')
    {
        player->pos.x += player->dir.x * MOVE;
        curr_x = (int)(player->pos.x);
    }
    if (new_y < map_info->height && new_y > 0 && map[new_y][curr_x] == '0')
        player->pos.y += player->dir.y * MOVE;
}

void    move_backward(t_player *player, char **map, t_map *map_info)
{
    int curr_x;
    int curr_y;
    int new_x;
    int new_y;

    new_x = (int)(player->pos.x - player->dir.x * (MOVE + 0.01));
    new_y = (int)(player->pos.y - player->dir.y * (MOVE + 0.01));
    curr_x = (int)(player->pos.x);
    curr_y = (int)(player->pos.y);
    if (new_x < map_info->width && new_x > 0 && map[curr_y][new_x] == '0')
        player->pos.x -= player->dir.x * MOVE;
        curr_x = (int)(player->pos.x);
    }
    if (new_y < map_info->height && new_y > 0 && map[new_y][curr_x] == '0')
        player->pos.y -= player->dir.y * MOVE;
}

void    move_right(t_player *player, char **map, t_map *map_info)
{
    int curr_x;
    int curr_y;
    int new_x;
    int new_y;

    new_x = (int)(player->pos.x + player->cam_plane.x * (MOVE + 0.01));
    new_y = (int)(player->pos.y + player->cam_plane.y * (MOVE + 0.01));
    curr_x = (int)(player->pos.x);
    curr_y = (int)(player->pos.y);
    if (new_x < map_info->width && new_x > 0 && map[curr_y][new_x] == '0') //TODO check if new case inside map limits
    {
        player->pos.x += player->cam_plane.x * MOVE;
        curr_x = (int)(player->pos.x);
    }
    if (new_y < map_info->height && new_y > 0 && map[new_y][curr_x] == '0') //TODO check if new case inside map limits
        player->pos.y += player->cam_plane.y * MOVE;
}

void    move_left(t_player *player, char **map, t_map *map_info)
{
    int curr_x;
    int curr_y;
    int new_x;
    int new_y;

    new_x = (int)(player->pos.x - player->cam_plane.x * (MOVE + 0.01));
    new_y = (int)(player->pos.y - player->cam_plane.y * (MOVE + 0.01));
    curr_x = (int)(player->pos.x);
    curr_y = (int)(player->pos.y);
    if (new_x < map_info->width && new_x > 0 && map[curr_y][new_x] == '0') //TODO check if new case inside map limits
    {
        player->pos.x -= player->cam_plane.x * MOVE;
        curr_x = (int)(player->pos.x);
    }
    if (new_y < map_info->height && new_y > 0 && map[new_y][curr_x] == '0') //TODO check if new case inside map limits
        player->pos.y -= player->cam_plane.y * MOVE;
}