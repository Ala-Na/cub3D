#include "renderer.h"

// gcc ./renderer/raycast_dda.c ./renderer/raycast_textures.c ./renderer/image_manip.c ./renderer/test.c -Lminilibx-linux/ -lmlx -lXext -lX11 -lm -L libft -g

int     key_press_hook(int keycode, t_param *param)
{
    printf("%i\n", keycode);
    if (keycode == ESC)
    {
        printf("EXIT\n");
        clean_exit(param);
    }
    else if (keycode == MOVE_FOWARD || keycode == MOVE_BACKWARD)
        move(keycode, param);
    else if (keycode == ROTATE_RIGHT || keycode == ROTATE_LEFT)
        rotate(keycode, param);
    return (0);
}

void    clean_exit(t_param *param)
{
    //mlx_destroy_image(param->mlx, param->prev_img->img);
    mlx_destroy_window(param->mlx, param->win);
    mlx_destroy_display(param->mlx);
    free(param->mlx);
    exit(0);  
}

void    draw_view(t_player *player, int map[I][J]) //FIXME test function only
{
    t_param param;
    t_img   img;

    param.mlx = mlx_init();
    param.win = mlx_new_window(param.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "test");
    img = generate_new_image(param.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (img.img == NULL)
        return; //TODO ADD ERROR, FREE MLX AND WIN
    raycasting_algorithm(&img, player, map);
    param.prev_img = &img;
    param.player = player;
    param.map[I][J] = map[I][J];
    mlx_put_image_to_window(param.mlx, param.win, img.img, 0, 0);
    mlx_hook(param.win, KeyPress, KeyPressMask, key_press_hook, &param);
    mlx_loop(param.mlx); 
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
/*
    int map[5][5] = {{1,1,1,1,1},{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{1,1,1,1,1}};
    */
    t_player    player;


    //In this example, player is directed towards West
    player.pos.x = 22.0;
    player.pos.y = 11.5;
    player.dir.x = -1.0;
    player.dir.y = 0.0;
    player.cam_plane.x = 0.0;
    player.cam_plane.y = 0.66; //To conserve FOV = 66°
    draw_view(&player, map);
    return (0);
}