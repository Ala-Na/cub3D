#include "renderer.h"

// gcc ./renderer/*.c -Lminilibx-linux/ -lmlx -lXext -lX11 -lm -Llibft -lft -g

int     close_win_hook(t_param *param)
{
    printf("EXIT\n");
    clean_exit(param);
}

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
    //FIXME Segfault with following
    //if (param->prev_img && param->prev_img->img != NULL)
    //    mlx_destroy_image(param->mlx, param->prev_img->img);
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

void    draw_view(t_player *player, char **map, char *text_path) //FIXME test function only
{
    t_param param;
    t_img   img;

    param.mlx = mlx_init();
    param.win = mlx_new_window(param.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "test");
    img = generate_new_image(param.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    param.texture = mlx_xpm_file_to_image(param.mlx, text_path, &(param.texture_width), &(param.texture_height));
    printf("tex width %i height %i\n", param.texture_width, param.texture_height);
    param.texture_buffer = (int*)mlx_get_data_addr(param.texture, &(param.text_bits_per_pixel), &(param.text_size_line), &(param.text_endian));
    if (param.texture_width != TEXTURE_WIDTH || param.texture_height != TEXTURE_HEIGHT) //FIXME Shouldn't be macro
    {
        printf("ERROR IN TEXTURE FOR TEST (MACRO AND DIMENSIONS ARE DIFFERENTS) !\n");
        return;
    }
    if (param.texture == NULL || img.img == NULL)
    {
        printf("ERROR EXIT\n");
        return; //TODO ADD ERROR, FREE MLX AND WIN
    }
    param.prev_img = &img;
    param.player = player;
    param.map = map;
    raycasting_algorithm(&param, &img, player, map);
    mlx_put_image_to_window(param.mlx, param.win, img.img, 0, 0);
    mlx_hook(param.win, KeyPress, KeyPressMask, key_press_hook, &param);
    mlx_hook(param.win, DestroyNotify, StructureNotifyMask, close_win_hook, &param);
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
    char *tex_path = "./renderer/blue_cheese.xpm";
    t_player    player;

    //In this example, player is directed towards West
    player.pos.y = 1.5;
    player.pos.x = 1.5;
    player.dir.y = -1.0;
    player.dir.x = 0.0;
    player.cam_plane.y = 0.0;
    player.cam_plane.x = 0.66; //To conserve FOV = 66°
    draw_view(&player, map, tex_path);
    return (0);
}