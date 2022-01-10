/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:29:25 by anadege           #+#    #+#             */
/*   Updated: 2022/01/10 16:21:12 by anadege          ###   ########.fr       */
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
# define SCREEN_WIDTH 1200
# define SCREEN_HEIGHT 1000
# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64
# define PITCH 100 //May be modified for jump/crunch ?
# define MOVE 1.0/3.0
# define ROTATE PI/8.0 //1/6 de quart de cercle en radian

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
}   t_ray;

typedef struct  s_stripe
{
    int     texture_number; //number of texture / corresponding texture
    int     high_pixel;
    int     low_pixel;
    t_ivec  hit_coord; //vector with x and y coordinate hit by ray
    double  pos;
}   t_stripe;

#endif