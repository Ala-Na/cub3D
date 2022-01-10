/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:31:12 by anadege           #+#    #+#             */
/*   Updated: 2022/01/10 16:24:10 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"
#include <stdio.h>

//TO TEST : gcc ./renderer/raycasting.c -L minilibx-linux -lmlx -lXext -lX11 - libft -g
// gcc ./renderer/raycasting.c ./minilibx-linux/libmlx.a ./minilibx-linux/libmlx_Linux.a -lXext -lX11 -lm -L libft -g

void    show_textured_wall(void *mlx, void *img, char *buffer, int size_line, int screen_x, t_stripe *stripe, int wall_height, int side)
{
    double          scale; //scaling/increase texture to screen scale
    int             screen_y;
    unsigned int    pixel_color; //Must be a Uint32 (unsigned int of 32 bits max)

    scale = 1.0 * TEXTURE_HEIGHT / wall_height;
    stripe->pos = (stripe->high_pixel - PITCH - SCREEN_HEIGHT / 2 + wall_height / 2) * scale;
    screen_y = stripe->high_pixel;
    while (screen_y < stripe->low_pixel)
    {
        stripe->hit_coord.y = (int)(stripe->pos) & (TEXTURE_HEIGHT - 1); // masking in case of overflow
        stripe->pos += scale;
        pixel_color =  mlx_get_color_value(mlx, 0xABCDEF);//FIXME test value
        //TODO pixel_color = texture[stripe->texture_number][TEXTURE_HEIGHT * strip->hit_coord->y + strip->hit_coord->x];
        //Make color darker for y-sides
        if (side == 1)
            pixel_color = (pixel_color >> 1) & 8355711;
        //TODO either stock pixel color in a buffer with buffer[screen_x][screen_y] = pixel color, or display pixel to screen_x/screen_y coordinates 
        buffer[(screen_y * size_line) + screen_x] = pixel_color; 
        screen_y++;
    }
}

int    get_texture_x_coordinate(int side, t_player *player, t_ray *ray) //need texture
{
    double  wall_hit_x; //x coordinate where wall was hit
    int     texture_hit_x; //corresponding x value where it should be hit

    if (side == 0) //wall was hit on x axis first
        wall_hit_x = player->pos.y + ray->wall_dist * ray->dir.y;
    else // wall was hit on y axis
        wall_hit_x = player->pos.x + ray->wall_dist * ray->dir.x;
    wall_hit_x -= floor((wall_hit_x)); //we substract the integer value rounded down to the nearest integer
    texture_hit_x = (int)(wall_hit_x * (double)(TEXTURE_WIDTH));
    if (side == 0 && ray->dir.x > 0)
        texture_hit_x = TEXTURE_WIDTH - texture_hit_x - 1;
    if (side == 1 && ray->dir.y < 0)
        texture_hit_x = TEXTURE_WIDTH - texture_hit_x - 1;
    return texture_hit_x;
}

int calculate_wall_height(int side, t_ray *ray)
{
    int height;

    if (side == 0) //wall was hit on x axis
        ray->wall_dist = ray->side_dist.x - ray->delta_dist.x;
    else //wall was hit on y axis
        ray->wall_dist = ray->side_dist.y - ray->delta_dist.y;
    height = (int)(SCREEN_HEIGHT / ray->wall_dist);
    return height;
}
 /* TODO decomment this function and add textures
int get_texture_number(int side, t_player *player, t_ray *ray)
{
    if (side == 1) //wall hited on y axis
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


void    get_textured_wall(void *mlx, void *img, char *buffer, int size_line, int side, t_player *player, t_ray *ray)
{
    int         wall_height;
    t_stripe    stripe;

    wall_height = calculate_wall_height(side, ray);
    //Searching lowest and highest pixel on current wall stripe to draw
    stripe.low_pixel = wall_height / 2 + SCREEN_HEIGHT / 2 + PITCH;
    if (stripe.low_pixel >= SCREEN_HEIGHT)
        stripe.low_pixel = SCREEN_HEIGHT - 1;
    stripe.high_pixel = -wall_height / 2 + SCREEN_HEIGHT / 2 + PITCH;
    if (stripe.high_pixel < 0)
        stripe.high_pixel = 0;
    //stripe.texture_number = get_texture_number(side, player, ray); //TODO decomment line
    stripe.hit_coord.x = get_texture_x_coordinate(side, player, ray);
    show_textured_wall(mlx, img, buffer, size_line, ray->screen_x, &stripe, wall_height, side);
}

int dda_algorithm(int map[24][24], t_ray *ray)
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
        {
            hit = true;
        }
    }
    return side;
}

int    dda(int map[24][24], t_player *player, t_ray *ray)
{
    bool    hit;
    bool    side;

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
    return dda_algorithm(map, ray);
}

void    raycasting_algorithm(void *mlx, void *img, char *buffer, int size_line, int map[24][24], t_player *player)
{
    t_ray   ray;
    int     side;

    ray.screen_x = 0;
    while (ray.screen_x < SCREEN_WIDTH) //We travel through the screen width
    {
        ray.box.x = (int)player->pos.x;
        ray.box.y = (int)player->pos.y;
        ray.cam_pos_x = 2 * ray.screen_x / (double)SCREEN_WIDTH - 1;
        ray.dir.x = player->dir.x + player->cam_plane.x * ray.cam_pos_x;
        ray.dir.y = player->dir.y + player->cam_plane.y * ray.cam_pos_x;
        if (ray.dir.x == 0)
            ray.delta_dist.x = 1e30;
        else
            ray.delta_dist.x = abs(1 / ray.dir.x);
        if (ray.dir.y == 0)
            ray.delta_dist.y = 1e30;
        else
            ray.delta_dist.y = abs(1 / ray.dir.y);
        side = dda(map, player, &ray);
        get_textured_wall(mlx, img, buffer, size_line, side, player, &ray);
        ray.screen_x++;
    }
}

void    draw_view(int map[24][24], t_player *player) //FIXME test function only
{
    void    *mlx;
    void    *win;
    void    *img;
    char    *buffer;
    int     bits_per_pixel;
    int     size_line;
    int     endian;

    bits_per_pixel = -1;
    size_line = -1;
    endian = -1;
    mlx = mlx_init();
    win = mlx_new_window(mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "test");
    img = mlx_new_image(mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    buffer = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
    raycasting_algorithm(mlx, img, buffer, size_line, map, player);
    mlx_put_image_to_window(mlx, win, img, 0, 0);
    sleep(5); //FIXME Forbidden function for mandatory, test purpose only
    mlx_destroy_image(mlx, img);
    mlx_destroy_window(mlx, win);
    mlx_destroy_display(mlx);
}

int main()
{
    int map[24][24] =
    {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
    {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
    {1,0,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1},
    {1,0,1,0,0,0,0,1,0,1,0,1,0,1,0,1,1,0,0,0,1,1,1,1},
    {1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1},
    {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
    {1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,1,0,0,0,1,1,1,1},
    {1,0,0,0,0,0,0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,1,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,0,0,1,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,1,1,0,1,1},
    {1,0,1,0,1,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,1},
    {1,0,0,1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,1,1,0,1,1},
    {1,0,1,0,1,0,0,0,0,1,1,0,1,1,0,0,1,0,0,1,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,1,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
    t_player    player;

    //In this example, player is directed towards West
    player.pos.x = 10.0;
    player.pos.y = 5.0;
    player.dir.x = -1.0;
    player.dir.y = 0.0;
    player.cam_plane.x = 0.0;
    player.cam_plane.y = 0.66; //To conserve FOV = 66°
    draw_view(map, &player);
    return (0);
}