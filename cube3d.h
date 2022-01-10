/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:22:43 by fmonbeig          #+#    #+#             */
/*   Updated: 2022/01/10 18:49:22 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

// +------------------------------------------+ //
//   System header files                        //
// +------------------------------------------+ //
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <X11/keysym.h>
# include <X11/X.h>

// +------------------------------------------+ //
//   Libft & other custom headers               //
// +------------------------------------------+ //

# include "libft/libft.h"
//# include "mlx.h"

// +------------------------------------------+ //
//   Structure                                  //
// +------------------------------------------+ //


typedef struct s_map
{
	char		height;
	char		width;
	char		player_orientation;
	float		player_height;
	float		player_width;
}				t_map;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_img;

typedef struct s_texture
{
	char	**temp;
	char	*no_file;
	char	*so_file;
	char	*we_file;
	char	*ea_file;
	int		f_file[3];
	int		c_file[3];
	t_img	*no;
	t_img	*so;
	t_img	*we;
	t_img	*ea;

}				t_texture;


typedef struct s_data
{
	void		*mlx;
	char		**map;
	t_map		map_info;
	t_texture	texture;

}				t_data;

// +------------------------------------------+ //
//   Typedef                                    //
// +------------------------------------------+ //
typedef int	t_bool;
// +------------------------------------------+ //
//   Define                                     //
// +------------------------------------------+ //
# define ERROR_NAME_MAP 		"ERROR: bad map extension\n"
# define ERROR_NB_ARGUMENT		"ERROR: wrong number of argument\n"
# define ERROR_GNL				"ERROR: bad read of the file\n"
# define ERROR_ELEMENT			"ERROR: Element are missing or are incorrect\n"
# define ERROR_ELEMENT_DOUBLON	"ERROR: Two element has the same name\n"
# define ERROR_COLOUR_WRONG_ELE	"ERROR: Wrong argument for colour definition\n"
# define ERROR_COLOUR_TOO_MANY	"ERROR: Too many argument for colour definition\n"
# define ERROR_COLOUR_NOT_RGB	"ERROR: Number must be between 0 and 255 for RGB\n"
# define ERROR_MAP_IS_TO_BIG	"ERROR: Map is to big\n"
# define ERROR_MALLOC			"ERROR: Malloc failed\n"
# define MAP_LIMIT				200
//TODO => Define les touches de clavier sur linux

// +------------------------------------------+ //
//   Check file                                  //
// +------------------------------------------+ //
void	check_file(char *map, t_data *data);

// +------------------------------------------+ //
//   Parsing                                    //
// +------------------------------------------+ //
void 	get_element(int fd, char *line, t_data *data);
t_bool	all_filled_up(t_data *data);
// +------------------------------------------+ //
//   ERROR and FREE                             //
// +------------------------------------------+ //
void	ft_error(char *str, t_data *data);
void	ft_error_during_gnl(char *error_message, int fd, char *line, t_data *data);
void	free_everything(t_data *data);
void	free_texture(t_texture *texture);

#endif

