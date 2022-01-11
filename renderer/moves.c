/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:33:27 by anadege           #+#    #+#             */
/*   Updated: 2022/01/11 21:59:57 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

void    move(int keycode, t_param *param)
{
    t_img   new_img;

    if (keycode == MOVE_FOWARD)
        move_foward(param->player, param->map);
    else
        move_backward(param->player, param->map);
    new_img = generate_new_image(param->mlx, SCREEN_WIDTH, SCREEN_WIDTH);
    if (new_img.img == NULL)
        return; //TODO ADD ERROR, FREE MLX AND WIN
    raycasting_algorithm(&new_img, param->player, param->map);
    mlx_put_image_to_window(param->mlx, param->win, new_img.img, 0, 0);
    if (param->prev_img->img != NULL)
        mlx_destroy_image(param->mlx, param->prev_img->img);
    param->prev_img = &new_img;
}

void    move_foward(t_player *player, char **map)
{
    int curr_x;
    int curr_y;
    int new_x;
    int new_y;

    new_x = (int)(player->pos.x + player->dir.x * (MOVE + 0.01));
    new_y = (int)(player->pos.y + player->dir.y * (MOVE + 0.01));
    curr_x = (int)(player->pos.x);
    curr_y = (int)(player->pos.y);
    if (new_x < I && map[curr_y][new_x] == '0')
    {
        player->pos.x += player->dir.x * MOVE;
        curr_x = (int)(player->pos.x);
    }
    if (new_y < J && map[new_y][curr_x] == '0')
        player->pos.y += player->dir.y * MOVE;
}

void    move_backward(t_player *player, char **map)
{
    int curr_x;
    int curr_y;
    int new_x;
    int new_y;

    new_x = (int)(player->pos.x - player->dir.x * (MOVE + 0.01));
    new_y = (int)(player->pos.y - player->dir.y * (MOVE + 0.01));
    curr_x = (int)(player->pos.x);
    curr_y = (int)(player->pos.y);
    if (new_x < I && map[curr_y][new_x] == '0')
    {
        player->pos.x -= player->dir.x * MOVE;
        curr_x = (int)(player->pos.x);
    }
    if (new_y < J && map[new_y][curr_x] == '0')
        player->pos.y -= player->dir.y * MOVE;
}

void    rotate(int keycode, t_param *param)
{
    t_img   new_img;

    if (keycode == ROTATE_RIGHT)
        rotate_right(param->player);
    else
        rotate_left(param->player);
    new_img = generate_new_image(param->mlx, SCREEN_WIDTH, SCREEN_WIDTH);
    if (new_img.img == NULL)
        return; //TODO ADD ERROR, FREE MLX AND WIN
    raycasting_algorithm(&new_img, param->player, param->map);
    mlx_put_image_to_window(param->mlx, param->win, new_img.img, 0, 0);
    if (param->prev_img->img != NULL)
        mlx_destroy_image(param->mlx, param->prev_img->img);
    param->prev_img = &new_img;
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