/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_manip.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:02:38 by anadege           #+#    #+#             */
/*   Updated: 2022/01/13 19:05:03 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** Function to convert RGB value to an exploitable int.
*/
int	convert_RGB_to_int(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

/*
** Function which returns a new t_img structure, filling it's information.
** Returns NULL in case of error.
*/
t_img    *generate_new_empty_image(t_data *data, int width, int height)
{
    t_img   *image;
    
    image = malloc(sizeof(*image));
    if (image == NULL)
        return NULL; //TODO ERROR MSG
    image->mlx = data->mlx;
    image->width = width;
    image->height = height;
    image->img = mlx_new_image(data->mlx, image->width, image->height);
    if (image->img == NULL)
        return NULL; //TODO ADD ERROR
    image->addr = mlx_get_data_addr(image->img, &(image->bits_per_pixel), &(image->line_length), &(image->endian));
    return image;
}

/*
** Function to fill a pixel of coordinates t_ivec pos with given pixel_color inside
** image t_img structure.
** If the number of bits_per_pixel isn't 32, color's value is modified to correct
** color with mlx_get_color_value.
** The pixel starting position (pixel_pos) corresponding to the first bit of a byte group
** is calculated (size_line = number of bytes per line, 4 = number of bits per byte).
** It differenciate cases where the most significant (alpha, endian == 0) or least
** significant (blue, endian == 1) byte is the first one expected by the image.
** It fill buffer as a char* with correct value thanks to bitshifting and masking.
*/
void    fill_img_buffer(t_data *data, t_img *img, t_ivec *pos, unsigned int pixel_color)
{
    int pixel_pos;

    if (img->bits_per_pixel != 32)
            pixel_color =  mlx_get_color_value(img->mlx, pixel_color);
    if (pos->x < 0 || pos->y < 0 || pos->x >= data->screen_width || pos->y >= data->screen_height)
        return; //TODO ERROR OUTSIDE SCREEN
    pixel_pos = (pos->y * img->line_length) + (pos->x * 4);
    if (img->endian == 1)
    {
        img->addr[pixel_pos + 0] = (pixel_color >> 24);
        img->addr[pixel_pos + 1] = (pixel_color >> 16) & 0xFF;
        img->addr[pixel_pos + 2] = (pixel_color >> 8) & 0xFF;
        img->addr[pixel_pos + 3] = (pixel_color) & 0xFF;
    }
    else if (img->endian == 0)
    {
        img->addr[pixel_pos + 0] = (pixel_color) & 0xFF;
        img->addr[pixel_pos + 1] = (pixel_color >> 8) & 0xFF;
        img->addr[pixel_pos + 2] = (pixel_color >> 16) & 0xFF;
        img->addr[pixel_pos + 3] = (pixel_color >> 24);
    }
}