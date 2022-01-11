#include "renderer.h"

// gcc ./renderer/*.c -Lminilibx-linux/ -lmlx -lXext -lX11 -lm -Llibft -lft -g

int     key_press_hook(int keycode, t_param *param)
{
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
    if (param->prev_img && param->prev_img->img != NULL)
        mlx_destroy_image(param->mlx, param->prev_img->img);
    mlx_destroy_window(param->mlx, param->win);
    mlx_destroy_display(param->mlx);
    free(param->mlx);
    int i = 0;
    while (i < J)
    {
        free(param->map[i]);
        i++;
    }
    free(param->map);
    exit(0);  
}

void    draw_view(t_player *player, char **map) //FIXME test function only
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
    param.map = map;
    mlx_put_image_to_window(param.mlx, param.win, img.img, 0, 0);
    mlx_hook(param.win, KeyPress, KeyPressMask, key_press_hook, &param);
    mlx_loop(param.mlx); 
}

int main()
{
    const char *str = "\
111111111111111111111111\n\
100000000000000010000001\n\
101000000000000000000001\n\
101000000000000000000001\n\
101000000000000010000001\n\
101000011111111111011111\n\
101000010101010110001111\n\
101000010000000110000001\n\
101000000000000000001111\n\
101000010000000110000001\n\
100000010000000110001111\n\
100000011110111111111111\n\
111111111110111111111111\n\
100000000000000000000001\n\
111111011110111111111111\n\
111111011110111111111111\n\
100000000110110000010001\n\
100000000000110010010001\n\
100000000110110000011011\n\
101010000110000010000001\n\
100100000110110000011011\n\
101010000110110010010001\n\
100000000110110000010001\n\
100000000000000000000001\n\
111111111111111111111111";
    char **map = ft_split(str, '\n');
    t_player    player;

    //In this example, player is directed towards West
    player.pos.y = 22.0;
    player.pos.x = 11.5;
    player.dir.y = -1.0;
    player.dir.x = 0.0;
    player.cam_plane.y = 0.0;
    player.cam_plane.x = 0.66; //To conserve FOV = 66°
    draw_view(&player, map);
    return (0);
}