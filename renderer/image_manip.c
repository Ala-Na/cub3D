/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_manip.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:02:38 by anadege           #+#    #+#             */
/*   Updated: 2022/01/11 16:01:07 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

/*
** Function which returns a new t_img structure, filling it's information.
** Returns NULL in case of error.
*/
t_img    generate_new_image(void *mlx, int width, int height)
{
    t_img   image;
    
    image.mlx = mlx;
    image.width = width;
    image.height = height;
    image.img = mlx_new_image(image.mlx, image.width, image.height);
    if (image.img == NULL)
        return image; //TODO ADD ERROR
    image.buffer = mlx_get_data_addr(image.img, &image.bits_per_pixel, &image.size_line, &image.endian);
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
void    fill_buffer(t_img *img, t_ivec *pos, unsigned int pixel_color)
{
    int             pixel_pos;

    if (img->bits_per_pixel != 32)
            pixel_color =  mlx_get_color_value(img->mlx, pixel_color);
    if (pos->x >= SCREEN_WIDTH || pos->y >= SCREEN_HEIGHT)
        return; //TODO ERROR OUTSIDE SCREEN
    pixel_pos = (pos->y * img->size_line) + (pos->x * 4);
    if (img->endian == 1)
    {
        img->buffer[pixel_pos + 0] = (pixel_color >> 24);
        img->buffer[pixel_pos + 1] = (pixel_color >> 16) & 0xFF;
        img->buffer[pixel_pos + 2] = (pixel_color >> 8) & 0xFF;
        img->buffer[pixel_pos + 3] = (pixel_color) & 0xFF;
    }
    else if (img->endian == 0)
    {
        img->buffer[pixel_pos + 0] = (pixel_color) & 0xFF;
        img->buffer[pixel_pos + 1] = (pixel_color >> 8) & 0xFF;
        img->buffer[pixel_pos + 2] = (pixel_color >> 16) & 0xFF;
        img->buffer[pixel_pos + 3] = (pixel_color >> 24);
    }
}