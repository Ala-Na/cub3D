//Following lodev raycasting's tutorial

#include <math.h>
#include <stdbool.h>

//TODO, define defqult screen width and height, default texture dimensions
#define PI 3.1415926535
//TODO Define move value : #define MOVE 1/3 * TILE

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
    double  cam_pos_x; //position of camera on x axis/screen, value between -1 and +1 (0 = screen's center)
    t_dvec  dir; //direction towards x/y axis of current ray, define angle
    t_ivec  box; //integer value of player's position
    t_dvec  side_dist; //distance to next x/y intercept from player's position
    t_dvec  delta_dist; //constant value which correspond to distance traveled by ray between to boxes on x/y axis
    double  wall_dist; //perpendicular ray's distance, to avoid fish eye effect
    t_ivec  step; //direction of ray vector on x/y, either +1 or -1
}   t_ray;

void    calculate_wall_height(int side, t_ray *ray)
{
    if 
}

int dda_algorithm(t_ray *ray)
{
    bool    hit;
    int     side;

    hit = false;
    while (hit == false)
    {
        if (ray->side_dist->x < ray->side_dist->y)
        {
            ray->side_dist->x += ray->delta_dist->x;
            ray->box->x += ray->step->x;
            side = 0;
        }
        else
        {
            ray->side_dist->y += ray->delta_dist->y;
            ray->box->y += ray->step->y;
            side = 1;
        }
        //TODO if map[ray->box->x][ray->box->y] != 0
        //TODO  hit = true;
    }
    return side;
}

int    dda(t_player player, t_ray *ray)
{
    bool    hit;
    bool    side;

    if (ray->dir->x < 0)
    {
        ray->*step->x = -1;
        ray->side_dist->x = (player->pos->x - ray->box->x) * ray->delta_dist->x;
    }
    else
    {
        ray->step->x = 1;
        ray->side_dist->x = (ray->box->x + 1.0 - player->pos->x) * ray->delta_dist->x;
    }
    if (ray->dir->y < 0)
    {
        ray->*step->y = -1;
        ray->side_dist->y = (player->pos->y - ray->box->y) * ray->delta_dist->y;
    }
    else
    {
        ray->step->y = 1;
        ray->side_dist->y = (ray->box->y + 1.0 - player->pos->y) * ray->delta_dist->y;
    }
    return dda_algorithm(ray);
}

void    raycasting_algorithm(t_player *player)
{
    int     i;
    t_ray   ray;

    ray.box->x = (int)player->pos->x;
    ray.box->y = (int)player->pos->y;
    while (i < SCREEN_WIDTH) //We travel through the screen width
    {
        ray.cam_pos_x = 2 * i / (double)SCREEN_WIDTH - 1;
        ray.dir_ray->x = player->dir->x + player->cam_plane->x * ray.cam_pos_x;
        ray.dir_ray->y = player->dir->y + player->cam_plane->y * ray.cam_pos_x;
        if (ray.dir->x == 0)
            ray.delta_dist->x = 1e30;
        else
            ray.delta_dist->x = abs(1 / ray->dir->x);
        if (ray.dir->y == 0)
            ray.delta_dist->y = 1e30;
        else
            ray.delta_dist->y = abs(1 / ray->dir->y);
        side = dda(player, &ray);
        calculate_wall_height(side, &ray);
    }
}

int main()
{
    t_player    player;

    //In this example, player is directed towards West
    player.pos->x = 10.0;
    player.pos->y = 5.0;
    player.dir->x = -1.0;
    player.dir->y = 0.0;
    player.cam_plane->x = 0.0;
    player.cam_plane->y = 0.66; //To conserve FOV = 66°
    return (0);
}