//Following lodev raycasting's tutorial

#include <math.h>
#include <stdbool.h>

//TODO, define defqult screen width and height, default texture dimensions
#define PI 3.1415926535
#define SCREEN_WIDTH 300
#define SCREEN_HEIGHT 250
#define PITCH 100 //May be modified for jump/crunch ?
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

int calculate_wall_height(int side, t_ray *ray)
{
    int height;

    if (side == 0)
        ray->wall_dist = ray->side_dist->x - ray->delta_dist->x;
    else
        ray->wall_dist = ray->side_dist->y - ray->delta_dist->y;
    height = (int)(SCREEN_HEIGHT / ray->wall_dist);
    return height;
}

void    show_textured_wall(int side, t_ray *ray)
{
    int wall_height;
    int low_pixel;
    int hight_pixel;

    wall_height = calculate_wall_height(side, ray);
    //Searching lowest and highest pixel on current wall stripe to draw
    low_pixel = wall_height / 2 + SCREEN_HEIGHT / 2 + PITCH;
    if (low_pixel >= SCREEN_HEIGHT)
        low_pixel = SCREEN_HEIGHT - 1;
    hight_pixel = -wall_height / 2 + SCREEN_HEIGHT / 2 + PITCH;
    if (hight_pixel < 0)
        hight_pixel = 0;
}

int dda_algorithm(t_ray *ray) //need map
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

int    dda(t_player player, t_ray *ray) //need map
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

void    raycasting_algorithm(t_player *player) //need map
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
        show_textured_wall(side, &ray);
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