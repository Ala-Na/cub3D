/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:33:27 by anadege           #+#    #+#             */
/*   Updated: 2022/01/10 14:33:28 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

void    move_foward(t_player *player)
{
    if //map[int(player->pos->x + player->dir->x * //move_value)][int(player->pos->y)] == 0: (NO WALL IN FRONT X)
        player->pos->x += player->dir->x * MOVE;
    if //map[int(player->pos->x)][int(player->pos->y + player->dir->y * //move_value)] == 0: (NO WALL IN FRONT Y)
        player->pos->y += player->dir->y * MOVE;
    //REDRAW
}

void    move_backward(t_player *player)
{
    if //map[int(player->pos->x - player->dir->x * //move_value)][int(player->pos->y)] == 0: (NO WALL IN FRONT X)
        player->pos->x -= player->dir->x * MOVE;
    if //map[int(player->pos->x)][int(player->pos->y - player->dir->y * //move_value)] == 0: (NO WALL IN FRONT Y)
        player->pos->y -= player->dir->y * MOVE;
    //REDRAW  
}

void    rotate_right(t_player *player)
{
    double  old_dir_x;
    double  old_cam_plane_x;

    old_dir_x = player->dir->x;
    old_cam_plane_x = player->cam_plane->x;
    player->dir->x = player->dir->x * cos(-ROTATE) - player->dir->y * sin(-ROTATE);
    player->dir->y = old_dir_x * sin(-ROTATE) + player->dir->y * cos(-ROTATE);
    player->cam_plane->x = player->cam_plane->x * cos(-ROTATE) - player->cam_plane->y * sin(-ROTATE); 
    player->cam_plane->y = old_cam_plane_x * sin(-ROTATE) + player->cam_plane->y * cps(-ROTATE);
    //REDRAW
}

void    rotate_left(t_player *player)
{
    double  old_dir_x;
    double  old_cam_plane_x;

    old_dir_x = player->dir->x;
    old_cam_plane_x = player->cam_plane->x;
    player->dir->x = player->dir->x * cos(ROTATE) - player->dir->y * sin(ROTATE);
    player->dir->y = old_dir_x * sin(ROTATE) + player->dir->y * cos(ROTATE);
    player->cam_plane->x = player->cam_plane->x * cos(ROTATE) - player->cam_plane->y * sin(ROTATE); 
    player->cam_plane->y = old_cam_plane_x * sin(ROTATE) + player->cam_plane->y * cps(ROTATE);  
    //REDRAW
}