/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:22:43 by fmonbeig          #+#    #+#             */
/*   Updated: 2022/01/13 11:53:46 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

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
# include <math.h>
# include <stdbool.h>

// +------------------------------------------+ //
//   Libft & other custom headers               //
// +------------------------------------------+ //

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"

// +------------------------------------------+ //
//   Structure                                  //
// +------------------------------------------+ //

typedef struct  t_dvec
{
    double  x;
    double  y;
}   t_dvec;

typedef struct  t_ivec
{
    int x;
    int y;
}   t_ivec;

typedef struct  s_player
{
    t_dvec  pos;
    t_dvec  dir;
    t_dvec  cam_plane;
}   t_player;

typedef struct s_map
{
	int			temp_h;
	int			temp_w;
	int			height;
	int			width;
	char		player_orientation;//FIXME add to t_player of data
	int			player_height;//FIXME add to t_player of data
	int			player_width;//FIXME add to t_player of data
}				t_map;

typedef struct s_img
{
	void	*mlx;
	void	*img;
	char	*addr; //buffer
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_img;

typedef struct s_texture
{
	char	**temp;
	int		flag_map;
	char	*no_file;
	char	*so_file;
	char	*we_file;
	char	*ea_file;
	int		**f_file;
	int		**c_file;
	t_img	*no;
	t_img	*so;
	t_img	*we;
	t_img	*ea;
}				t_texture;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	char		**map;
	t_map		*map_info;
	t_texture	*textures;
	t_player	*player;
	t_img		*img;
}				t_data;

typedef struct  s_ray
{
    int     screen_x;
    double  cam_pos_x;
    t_dvec  dir;
    t_ivec  box;
    t_dvec  side_dist;
    t_dvec  delta_dist;
    double  wall_dist;
    t_ivec  step;
    int     side;
}   t_ray;

typedef struct  s_stripe
{
    int     texture_number;
    int     high_pixel;
    int     low_pixel;
    t_ivec  hit_coord;
    double  pos;
}   t_stripe;


// +------------------------------------------+ //
//   Typedef                                    //
// +------------------------------------------+ //
typedef int	t_bool;
// +------------------------------------------+ //
//   Define                                     //
// +------------------------------------------+ //
// Define for parsing
# define ERROR_NAME_MAP 		"ERROR\nBad map extension\n"
# define ERROR_NB_ARGUMENT		"ERROR\nWrong number of argument\n"
# define ERROR_GNL				"ERROR\nBad read of the file\n"
# define ERROR_ELEMENT			"ERROR\nElement are missing or are incorrect\n"
# define ERROR_ELEMENT_DOUBLON	"ERROR\nTwo element has the same name\n"
# define ERROR_COLOUR_WRONG_ELE	"ERROR\nWrong argument for colour definition\n"
# define ERROR_COLOUR_TOO_MANY	"ERROR\nToo many argument for colour definition\n"
# define ERROR_NO_COLOUR		"ERROR\nNot enough argument for colour definition\n"
# define ERROR_COLOUR_NOT_RGB	"ERROR\nNumber must be between 0 and 255 for RGB\n"
# define ERROR_MAP_IS_TO_BIG	"ERROR\nMap is to big\n"
# define ERROR_MAP_EMPTY_LINE	"ERROR\nMap have an empty line\n"
# define ERROR_MAP_NOT_CLOSE	"ERROR\nMap is not close\n"
# define ERROR_MAP_WRONG_ELE	"ERROR\nMap have wrong element\n"
# define ERROR_TWO_PLAYERS		"ERROR\nMap have more than one player\n"
# define ERROR_NO_PLAYER		"ERROR\nNo player, No game :(\n"
# define ERROR_MALLOC			"ERROR\nMalloc failed\n"

// Define for maths calculations
# define PI 3.1415926535
# define PITCH 100
# define MOVE 1.0/3.0
# define ROTATE PI/8.0

// Define for keyboard qwerty linux
# define MOVE_FOWARD 119
# define MOVE_BACKWARD 115
# define MOVE_LEFT 97
# define MOVE_RIGHT 100
# define ROTATE_RIGHT 65363
# define ROTATE_LEFT 65361
# define ESC 65307
// +------------------------------------------+ //
//   Check file and map                         //
// +------------------------------------------+ //
void	check_file(char *map, t_data *data);
void	check_map(t_data *data);
void	get_info_map(char *file, t_data *data);
void	check_one(char *line, t_data *data);
void	check_close(int height, t_data *data);
void	get_player_position(int height, t_data *data);
// +------------------------------------------+ //
//   Parsing                                    //
// +------------------------------------------+ //
void 	get_element(int fd, char *line, t_data *data);
void	get_map(int fd, char *line, t_data *data);
t_bool	all_filled_up(t_data *data);
// +------------------------------------------+ //
//   ERROR and FREE                             //
// +------------------------------------------+ //
void	ft_error(char *str, t_data *data);
void	ft_error_during_gnl(char *error_message, int fd, char *line, t_data *data);
void	free_everything(t_data *data);
void	free_texture(t_data *data);

#endif

