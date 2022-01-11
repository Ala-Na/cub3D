/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 16:23:08 by anadege           #+#    #+#             */
/*   Updated: 2022/01/11 16:26:59 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

void    show_textured_wall(t_img *img, t_ray *ray, t_stripe *stripe, int wall_height)
{
    double          scale; //scaling/increase texture to screen scale
    t_ivec          pixel_pos;
    unsigned int    pixel_color; //Must be a Uint32 (unsigned int of 32 bits max)

    scale = 1.0 * TEXTURE_HEIGHT / wall_height;
    stripe->pos = (stripe->high_pixel - PITCH - SCREEN_HEIGHT / 2 + wall_height / 2) * scale;
    pixel_pos.x = ray->screen_x;
    pixel_pos.y = stripe->high_pixel;
    while (pixel_pos.y < stripe->low_pixel)
    {
        stripe->hit_coord.y = (int)(stripe->pos) & (TEXTURE_HEIGHT - 1); // masking in case of overflow
        stripe->pos += scale;
        pixel_color = 0xABCDEF; //TODO Test version. True version : pixel_color = texture[stripe->texture_number][TEXTURE_HEIGHT * strip->hit_coord->y + strip->hit_coord->x];
        //Make color darker for y-sides
        if (ray->side == 1)
            pixel_color = (pixel_color >> 1) & 8355711;
        fill_buffer(img, &pixel_pos, pixel_color);
        pixel_pos.y++;
    }
}

int    get_texture_x_coordinate(t_player *player, t_ray *ray)
{
    double  wall_hit_x;
    int     texture_hit_x;

    if (ray->side == 0)
        wall_hit_x = player->pos.y + ray->wall_dist * ray->dir.y;
    else
        wall_hit_x = player->pos.x + ray->wall_dist * ray->dir.x;
    wall_hit_x -= floor((wall_hit_x));
    texture_hit_x = (int)(wall_hit_x * (double)(TEXTURE_WIDTH));
    if (ray->side == 0 && ray->dir.x > 0)
        texture_hit_x = TEXTURE_WIDTH - texture_hit_x - 1;
    if (ray->side == 1 && ray->dir.y < 0)
        texture_hit_x = TEXTURE_WIDTH - texture_hit_x - 1;
    return texture_hit_x;
}

 /* TODO decomment this function and add textures
int get_texture_number(t_player *player, t_ray *ray)
{
    if (ray->side == 1) //wall hited on y axis
    {
        if (player->dir->y > 0)
            return //NORTH TEXTURE;
        return //SOUTH TEXTURE;
    }
    if (player->dir->x > 0)
        return //EST TEXTURE;
    return //WEST TEXTURE;
}
*/

void    get_textured_wall(t_img *img, t_player *player, t_ray *ray, int wall_height)
{
    t_stripe    stripe;

    stripe.low_pixel = wall_height / 2 + SCREEN_HEIGHT / 2 + PITCH;
    if (stripe.low_pixel >= SCREEN_HEIGHT)
        stripe.low_pixel = SCREEN_HEIGHT - 1;
    stripe.high_pixel = -wall_height / 2 + SCREEN_HEIGHT / 2 + PITCH;
    if (stripe.high_pixel < 0)
        stripe.high_pixel = 0;
    //stripe.texture_number = get_texture_number(player, ray); //TODO decomment line
    stripe.hit_coord.x = get_texture_x_coordinate(player, ray);
    show_textured_wall(img, ray, &stripe, wall_height);
}