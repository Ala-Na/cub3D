/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 16:23:08 by anadege           #+#    #+#             */
/*   Updated: 2022/01/13 18:09:02 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int get_corresponding_pixel_color(t_stripe *stripe, t_img *texture, double scale)
{
    int pixel_color;

    stripe->hit_coord.y = (int)(stripe->pos);
    if (stripe->hit_coord.y < 0)
        stripe->hit_coord.y = 0;
    else if (stripe->hit_coord.y >= texture->height)
        stripe->hit_coord.y = texture->height -1;
    stripe->pos += scale;
    pixel_color = (int)((int*)texture->addr)[(texture->line_length / 4) * stripe->hit_coord.y + stripe->hit_coord.x];
    return pixel_color;
}

void    show_textured_wall(t_data *data, t_ray *ray, t_stripe *stripe, int wall_height)
{
    double          scale;
    t_ivec          pixel_pos;
    int             pixel_color;

    scale = 1.0 * stripe->texture->height / wall_height;
    stripe->pos = (stripe->high_pixel - PITCH - data->screen_height / 2 + wall_height / 2) * scale;
    pixel_pos.x = ray->screen_x;
    pixel_pos.y = 0;
    while (pixel_pos.y < stripe->high_pixel)
    {
        pixel_color = data->texture->c_value;
        fill_img_buffer(data, data->img, &pixel_pos, pixel_color);
        pixel_pos.y++;
    }
    while (pixel_pos.y < stripe->low_pixel)
    {
        pixel_color = get_corresponding_pixel_color(stripe, stripe->texture, scale);
        if (ray->side == 1)
            pixel_color = (pixel_color >> 1) & 8355711;
        fill_img_buffer(data, data->img, &pixel_pos, pixel_color);
        pixel_pos.y++;
    }
    while (pixel_pos.y < data->screen_height)
    {
        pixel_color = data->texture->f_value;
        fill_img_buffer(data, data->img, &pixel_pos, pixel_color);
        pixel_pos.y++;
    }
}

int    get_texture_x_coordinate(t_player *player, t_img *texture, t_ray *ray)
{
    double  wall_hit_x;
    int     texture_hit_x;

    if (ray->side == 0)
        wall_hit_x = player->pos.y + ray->wall_dist * ray->dir.y;
    else
        wall_hit_x = player->pos.x + ray->wall_dist * ray->dir.x;
    wall_hit_x -= floor((wall_hit_x));
    texture_hit_x = (int)(wall_hit_x * (double)(texture->width));
    if (ray->side == 0 && ray->dir.x < 0)
        texture_hit_x = texture->width - texture_hit_x - 1;
    if (ray->side == 1 && ray->dir.y > 0)
        texture_hit_x = texture->width - texture_hit_x - 1;
    return texture_hit_x;
}

//TODO check if correct texture for side with tests
t_img   *get_corresponding_texture(t_data *data, t_ray *ray)
{
    if (ray->side == 1)
    {
        if (data->player->dir.y > 0)
            return &data->texture->no;
        return &data->texture->so;
    }
    if (data->player->dir.x > 0)
        return &data->texture->ea;
    return &data->texture->we;
}

void    raycast_textured_wall(t_data *data, t_ray *ray, int wall_height)
{
    t_stripe    stripe;

    stripe.low_pixel = wall_height / 2 + data->screen_height / 2 + PITCH;
    if (stripe.low_pixel >= data->screen_height)
        stripe.low_pixel = data->screen_height - 1;
    stripe.high_pixel = -wall_height / 2 + data->screen_height / 2 + PITCH;
    if (stripe.high_pixel < 0)
        stripe.high_pixel = 0;
    stripe.texture = get_corresponding_texture(data, ray);
    stripe.hit_coord.x = get_texture_x_coordinate(data->player, stripe.texture, ray);
    show_textured_wall(data, ray, &stripe, wall_height);
}