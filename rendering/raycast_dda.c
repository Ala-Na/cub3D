/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:31:12 by anadege           #+#    #+#             */
/*   Updated: 2022/01/13 17:49:48 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int calculate_wall_height(t_ray *ray, int screen_height)
{
    int height;

    if (ray->side == 0)
        ray->wall_dist = ray->side_dist.x - ray->delta_dist.x;
    else
        ray->wall_dist = ray->side_dist.y - ray->delta_dist.y;
    height = (int)(screen_height / ray->wall_dist);
    return height;
}

int differential_diagnosis_analysis(t_ray *ray, char **map)
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
        if (map[ray->box.y][ray->box.x] != '0')
            hit = true;
    }
    return side;
}

int    init_differential_diagnosis_analysis(t_data *data, t_ray *ray)
{
    if (ray->dir.x < 0)
    {
        ray->step.x = -1;
        ray->side_dist.x = (data->player->pos.x - ray->box.x) * ray->delta_dist.x;
    }
    else
    {
        ray->step.x = 1;
        ray->side_dist.x = (ray->box.x + 1.0 - data->player->pos.x) * ray->delta_dist.x;
    }
    if (ray->dir.y < 0)
    {
        ray->step.y = -1;
        ray->side_dist.y = (data->player->pos.y - ray->box.y) * ray->delta_dist.y;
    }
    else
    {
        ray->step.y = 1;
        ray->side_dist.y = (ray->box.y + 1.0 - data->player->pos.y) * ray->delta_dist.y;
    }
    return differential_diagnosis_analysis(ray, data->map);
}

void    raycasting_algorithm(t_data *data)
{
    t_ray   ray;
    int     wall_height;

    ray.screen_x = 0;
    while (ray.screen_x < data->screen_width)
    {
        ray.box.x = (int)data->player->pos.x;
        ray.box.y = (int)data->player->pos.y;
        ray.cam_pos_x = 2 * ray.screen_x / (double)data->screen_width - 1;
        ray.dir.x = data->player->dir.x + data->player->cam_plane.x * ray.cam_pos_x;
        ray.dir.y = data->player->dir.y + data->player->cam_plane.y * ray.cam_pos_x;
        if (ray.dir.x == 0)
            ray.delta_dist.x = 1e30;
        else
            ray.delta_dist.x = fabs(1 / ray.dir.x);
        if (ray.dir.y == 0)
            ray.delta_dist.y = 1e30;
        else
            ray.delta_dist.y = fabs(1 / ray.dir.y);
        if (isnan(ray.delta_dist.x) != 0 || isnan(ray.delta_dist.y) != 0)
            return; //TODO take error into account
        ray.side = init_differential_diagnosis_analysis(data, &ray);
        wall_height = calculate_wall_height(&ray, data->screen_height);
        raycast_textured_wall(data, &ray, wall_height);
        ray.screen_x++;
    }
}