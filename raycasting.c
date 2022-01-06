#include <math.h>

typedef struct  s_player
{
    float   x; //x's player position
    float   y; //y's player position
    float   angle; //player view center angle orientation
    int     field_view; //fixed value corresponding to the length of field view, set to 60
}   t_player;

typedef struct  s_ray
{
    t_player    player; //ray need to access player position
    // TO_CALCULATE FROM PLAYER POSITION
    float       ray_angle; //angle of concerned ray, included inside +/- 30 to player angle 
    float       delta_x; //offset from tile corner (digits after . of player's x)
    float       delta_y; //offset from tile corner (digits after . of player's y)
    // TO_CALCULATE WITH MATHS
    int         tile_step_x; //ray angle direction towards x, equal to +1 or -1
    int         tile_step_y; //ray angle direction towards y, equal to +1 or -1
    float       x_step; //distance to next intersect meeted by ray on x, equal to tan(ray_angle)
    float       y_step; //distance to next intersect meeted by ray on y, equal to 1/tan(ray_angle)
    float       x_intercept; //intersect point on x, = x + delta_x + -delta_y / tan(ray_angle)
    float       y_intercept; //intersect point on y, = y + de;ta_y + delta_x / tan(ray_angle)
    // TO_CALCULATE FROM REST
    float       shortest_distance; //shortest distance to wall encoutered by ray, on x or y, with calculation to avoid fish_eye effect
    float       wall_height; //height of wall calculated from distance
};

typedef struct s_moves
{
    float   pos_mod; //value to add or substract to x or y on map
    float   ang_mod; //value to add to angle to move point of view horizontally
};
