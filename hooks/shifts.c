/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shifts.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 12:05:41 by anadege           #+#    #+#             */
/*   Updated: 2022/01/13 17:31:15 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    move(int keycode, t_data *data)
{
    t_img   new_img;

    if (keycode == MOVE_FOWARD)
        move_foward(data->player, data->map);
    else if (keycode == MOVE_BACKWARD)
        move_backward(data->player, data->map);
    else if (keycode == MOVE_RIGHT)
        move_right(data->player, data->map);
    else
        move_left(data->player, data->map);
    new_img = generate_new_image(data->mlx, SCREEN_WIDTH, SCREEN_WIDTH);
    if (new_img.img == NULL)
        return; //TODO ADD ERROR, FREE MLX AND WIN
    raycasting_algorithm(data, &new_img, data->player, data->map);
    mlx_put_image_to_window(data->mlx, data->win, new_img.img, 0, 0);
    if (data->prev_img->img != NULL)
        mlx_destroy_image(data->mlx, data->prev_img->img);
    data->prev_img = &new_img;
}

void    move_foward(t_player *player, char **map, t_map *map_infos)
{
    int curr_x;
    int curr_y;
    int new_x;
    int new_y;

    new_x = (int)(player->pos.x + player->dir.x * (MOVE + 0.01));
    new_y = (int)(player->pos.y + player->dir.y * (MOVE + 0.01));
    curr_x = (int)(player->pos.x);
    curr_y = (int)(player->pos.y);
    if (map[curr_y][new_x] == '0') //TODO check if new case inside map limits
    {
        player->pos.x += player->dir.x * MOVE;
        curr_x = (int)(player->pos.x);
    }
    if (map[new_y][curr_x] == '0') //TODO check if new case inside map limits
        player->pos.y += player->dir.y * MOVE;
}

void    move_backward(t_player *player, t_map *map)
{
    int curr_x;
    int curr_y;
    int new_x;
    int new_y;

    new_x = (int)(player->pos.x - player->dir.x * (MOVE + 0.01));
    new_y = (int)(player->pos.y - player->dir.y * (MOVE + 0.01));
    curr_x = (int)(player->pos.x);
    curr_y = (int)(player->pos.y);
    if (map[curr_y][new_x] == '0') //TODO check if new case inside map limits
    {
        player->pos.x -= player->dir.x * MOVE;
        curr_x = (int)(player->pos.x);
    }
    if (map[new_y][curr_x] == '0') //TODO check if new case inside map limits
        player->pos.y -= player->dir.y * MOVE;
}

void    move_right(t_player *player, t_map *map)
{
    int curr_x;
    int curr_y;
    int new_x;
    int new_y;

    new_x = (int)(player->pos.x + player->cam_plane.x * (MOVE + 0.01));
    new_y = (int)(player->pos.y + player->cam_plane.y * (MOVE + 0.01));
    curr_x = (int)(player->pos.x);
    curr_y = (int)(player->pos.y);
    if (map[curr_y][new_x] == '0') //TODO check if new case inside map limits
    {
        player->pos.x += player->cam_plane.x * MOVE;
        curr_x = (int)(player->pos.x);
    }
    if (map[new_y][curr_x] == '0') //TODO check if new case inside map limits
        player->pos.y += player->cam_plane.y * MOVE;
}

void    move_left(t_player *player, t_map *map)
{
    int curr_x;
    int curr_y;
    int new_x;
    int new_y;

    new_x = (int)(player->pos.x - player->cam_plane.x * (MOVE + 0.01));
    new_y = (int)(player->pos.y - player->cam_plane.y * (MOVE + 0.01));
    curr_x = (int)(player->pos.x);
    curr_y = (int)(player->pos.y);
    if (map[curr_y][new_x] == '0') //TODO check if new case inside map limits
    {
        player->pos.x -= player->cam_plane.x * MOVE;
        curr_x = (int)(player->pos.x);
    }
    if (map[new_y][curr_x] == '0') //TODO check if new case inside map limits
        player->pos.y -= player->cam_plane.y * MOVE;
}