/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:29:25 by anadege           #+#    #+#             */
/*   Updated: 2022/01/12 17:02:43 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H
# define RENDERER_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <X11/keysym.h>
# include <X11/X.h>

# define PI 3.1415926535
# define PITCH 100 //May be modified for jump/crunch ?
# define MOVE 1.0/3.0
# define ROTATE PI/8.0 //1/6 de quart de cercle en radian

//FIXME tests define to delete
# define I 24
# define J 25
# define SCREEN_WIDTH 1200
# define SCREEN_HEIGHT 1000
# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64

//FIXME modify by wasd value
# define MOVE_FOWARD 65362
# define MOVE_BACKWARD 65364
# define ROTATE_RIGHT 65363
# define ROTATE_LEFT 65361
# define ESC 65307

//Struct for 2D vector of doubles values
typedef struct  t_dvec
{
    double  x;
    double  y;
}   t_dvec;

//Struct for 2D vector of integer values
typedef struct  t_ivec
{
    int x;
    int y;
}   t_ivec;

typedef struct  s_player
{
    t_dvec  pos; //player position
    t_dvec  dir; //direction towards x/y axis, define angle
    t_dvec  cam_plane; //player's camera plane, must be perpendicular to player's direction and y equal to FOV (0.66)
}   t_player;

typedef struct  s_ray
{
    int     screen_x;
    double  cam_pos_x; //position of camera on x axis/screen, value between -1 and +1 (0 = screen's center)
    t_dvec  dir; //direction towards x/y axis of current ray, define angle
    t_ivec  box; //integer value of player's position
    t_dvec  side_dist; //distance to next x/y intercept from player's position
    t_dvec  delta_dist; //constant value which correspond to distance traveled by ray between to boxes on x/y axis
    double  wall_dist; //perpendicular ray's distance, to avoid fish eye effect
    t_ivec  step; //direction of ray vector on x/y, either +1 or -1
    int     side; //equal to 0 if wall hit on x-axis, 1 if y-axis
}   t_ray;

typedef struct  s_stripe
{
    int     texture_number; //number of texture / corresponding texture
    int     high_pixel;
    int     low_pixel;
    t_ivec  hit_coord; //vector with x and y coordinate hit by ray
    double  pos;
}   t_stripe;

typedef struct  s_img
{
    void    *mlx;
    void    *img;
    int     width;
    int     height;
    char    *buffer;
    int     bits_per_pixel;
    int     size_line;
    int     endian;
}   t_img;

typedef struct  s_param
{
    void        *mlx;
    void        *win;
    t_player    *player;
    char         **map;
    t_img       *prev_img;
    void        *texture;
    int         *texture_buffer;
    int         text_bits_per_pixel;
    int         text_size_line;
    int         text_endian;
    int         texture_width;
    int         texture_height;
}   t_param;

//FIXME test functions to delete
void    draw_view(t_player *player, char **map, char *text_path);
void    clean_exit(t_param *param);
int     key_press_hook(int keycode, t_param *param);

/*
** Functions for raycasting algorithm
*/
void    raycasting_algorithm(t_param *param, t_img *img, t_player *player, char **map);
int     dda(t_player *player, t_ray *ray, char **map);
int     dda_algorithm(t_ray *ray, char **map);
void    get_textured_wall(t_param *param, t_img *img, t_player *player, t_ray *ray, int wall_height);
int     calculate_wall_height(t_ray *ray);
int     get_texture_x_coordinate(t_player *player, t_ray *ray);
void    show_textured_wall(t_param *param, t_img *img, t_ray *ray, t_stripe *stripe, int wall_height);

/*
** Functions for image management
*/
t_img   generate_new_image(void *mlx, int width, int height);
void    fill_buffer(t_img *img, t_ivec *pos, unsigned int pixel_color);

/*
** Movements
*/
void    move(int keycode, t_param *param);
void    move_foward(t_player *player, char **map);
void    move_backward(t_player *player, char **map);
void    rotate(int keycode, t_param *param);
void    rotate_right(t_player *player);
void    rotate_left(t_player *player);

#endif