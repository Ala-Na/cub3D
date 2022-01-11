/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:31:12 by anadege           #+#    #+#             */
/*   Updated: 2022/01/11 16:26:16 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"
#include <stdio.h>

int calculate_wall_height(t_ray *ray)
{
    int height;

    if (ray->side == 0)
        ray->wall_dist = ray->side_dist.x - ray->delta_dist.x;
    else
        ray->wall_dist = ray->side_dist.y - ray->delta_dist.y;
    height = (int)(SCREEN_HEIGHT / ray->wall_dist);
    return height;
}

int dda_algorithm(t_ray *ray, int map[I][J])
{
    bool    hit;
    int     side;

    hit = false;
    while (hit == false)
    {
        if (ray->side_dist.x < ray->side_dist.y)
        {
            ray->side_dist.x += ray->delta_dist.x;
            ray->box.x += ray->step.x;
            side = 0;
        }
        else
        {
            ray->side_dist.y += ray->delta_dist.y;
            ray->box.y += ray->step.y;
            side = 1;
        }
        if (map[ray->box.x][ray->box.y] > 0)
            hit = true;
    }
    return side;
}

int    dda(t_player *player, t_ray *ray, int map[I][J])
{
    if (ray->dir.x < 0)
    {
        ray->step.x = -1;
        ray->side_dist.x = (player->pos.x - ray->box.x) * ray->delta_dist.x;
    }
    else
    {
        ray->step.x = 1;
        ray->side_dist.x = (ray->box.x + 1.0 - player->pos.x) * ray->delta_dist.x;
    }
    if (ray->dir.y < 0)
    {
        ray->step.y = -1;
        ray->side_dist.y = (player->pos.y - ray->box.y) * ray->delta_dist.y;
    }
    else
    {
        ray->step.y = 1;
        ray->side_dist.y = (ray->box.y + 1.0 - player->pos.y) * ray->delta_dist.y;
    }
    return dda_algorithm(ray, map);
}

void    raycasting_algorithm(t_img *img, t_player *player, int map[I][J])
{
    t_ray   ray;
    int     side;
    int     wall_height;

    ray.screen_x = 0;
    while (ray.screen_x < SCREEN_WIDTH)
    {
        ray.box.x = (int)player->pos.x;
        ray.box.y = (int)player->pos.y;
        ray.cam_pos_x = 2 * ray.screen_x / (double)SCREEN_WIDTH - 1;
        ray.dir.x = player->dir.x + player->cam_plane.x * ray.cam_pos_x;
        ray.dir.y = player->dir.y + player->cam_plane.y * ray.cam_pos_x;
        if (ray.dir.x == 0)
            ray.delta_dist.x = 1e30;
        else
            ray.delta_dist.x = fabs(1 / ray.dir.x);
        if (ray.dir.y == 0)
            ray.delta_dist.y = 1e30;
        else
            ray.delta_dist.y = fabs(1 / ray.dir.y);
        ray.side = dda(player, &ray, map);
        wall_height = calculate_wall_height(&ray);
        get_textured_wall(img, player, &ray, wall_height);
        ray.screen_x++;
    }
}