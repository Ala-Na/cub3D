/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:22:43 by fmonbeig          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/01/14 17:34:01 by fmonbeig         ###   ########.fr       */
=======
/*   Updated: 2022/01/14 16:50:19 by anadege          ###   ########.fr       */
>>>>>>> 40959e7 (norme)
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
# include <sys/stat.h>
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
}	t_dvec;

typedef struct  t_ivec
{
	int x;
	int y;
}	t_ivec;

typedef struct  s_player
{
	t_dvec  pos;
	t_dvec  dir;
	t_dvec  cam_plane;
}	t_player;

typedef struct s_map
{
	int			height;
	int			width;
}				t_map;

typedef struct s_img
{
	void	*mlx;
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
	int		flag_map;
	char	*no_file;
	char	*so_file;
	char	*we_file;
	char	*ea_file;
	int		**f_file;
	int		**c_file;
	int		f_value;
	int		c_value;
	t_img	no;
	t_img	so;
	t_img	we;
	t_img	ea;
}				t_texture;

typedef struct s_data
{
	void		*mlx;
	int			screen_width;
	int			screen_height;
	void		*win;
	char		**map;
	t_map		*map_info;
	t_texture	*texture;
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
	int		wall_height;
}   t_ray;

typedef struct  s_stripe
{
    t_img	*texture;
    int     high_pixel;
    int     low_pixel;
    t_ivec  hit_coord;
    double  pos;
}   t_stripe;

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
# define ERROR_MAP_IS_NOT_REAL	"ERROR\nVery funny... Where is the map ?\n"
# define ERROR_MAP_NOT_CLOSE	"ERROR\nMap is not close\n"
# define ERROR_MAP_WRONG_ELE	"ERROR\nMap have wrong element\n"
# define ERROR_TWO_PLAYERS		"ERROR\nMap have more than one player\n"
# define ERROR_NO_PLAYER		"ERROR\nNo player, No game :(\n"
# define ERROR_DIRECTORY		"ERROR\nOops... the file is a directory\n"
# define ERROR_MALLOC			"ERROR\nMalloc failed\n"
# define ERROR_IMG				"ERROR\nMlx image error\n"
# define ERROR_MLX				"ERROR\nMlx can't be launched\n"
# define ERROR_PIXEL			"ERROR\nPixel outside screen's limits\n"
# define ERROR_WINDOW			"ERROR\nMlx window can't be launched\n"
# define ERROR_CALCULATION		"ERROR\nError in calculation\n"

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
void	check_one(char *line, t_data *data);
void	check_close(int height, t_data *data);
void	check_extension(char *file, t_data *data);

// +------------------------------------------+ //
//   Parsing                                    //
// +------------------------------------------+ //
void 	get_element(int fd, char *line, t_data *data);
void	get_map(int fd, char *line, t_data *data);
void	get_info_map(char *file, t_data *data);
void	get_player_position(int height, t_data *data);
void	filled_floor_or_ceiling(int fd, char *line, t_data *data, char c);
bool	all_filled_up(t_data *data);

// +------------------------------------------+ //
//   Images initialization                      //
// +------------------------------------------+ //
void	init_img(t_data *data);

// +------------------------------------------+ //
//   PRINT                                      //
// +------------------------------------------+ //
void	print_parsing(t_data *data);

// +------------------------------------------+ //
//   Get colour utils                           //
// +------------------------------------------+ //
void	error_doublon_c_file(int fd, char *line, t_data *data);
void	error_doublon_f_file(int fd, char *line, t_data *data);
void	error_no_colour(int fd, char *line, t_data *data, int i);

// +------------------------------------------+ //
//   ERROR and FREE                             //
// +------------------------------------------+ //
void	ft_error(char *str, t_data *data);
void	ft_error_during_gnl(char *error_message, int fd, char *line, t_data *data);
void	free_everything(t_data *data);
void	free_texture(t_data *data);

// +------------------------------------------+ //
//   Functions to initialize raycasting         //
// +------------------------------------------+ //
void    launch_engine(t_data *data);
void	modify_map(t_data *data);
void    convert_floor_and_ceiling_colors(t_data *data);

// +------------------------------------------+ //
//   Raycasting 'flat' rendering                //
// +------------------------------------------+ //
void	raycasting_algorithm(t_data *data, t_img *img);
void	calculate_distance_deltas(t_data *data, t_img *img, t_ray *ray);
int		init_differential_diagnosis_analysis(t_data *data, t_ray *ray);
int		differential_diagnosis_analysis(t_ray *ray, char **map);
int		calculate_wall_height(t_ray *ray, int screen_height);

// +------------------------------------------+ //
//   Raycasting 'textured' rendering            //
// +------------------------------------------+ //
void	raycast_textured_wall(t_data *data, t_ray *ray, t_img *img);
t_img   *get_corresponding_texture(t_data *data, t_ray *ray);
int		get_texture_x_coordinate(t_player *player, t_img *texture, t_ray *ray);
void    show_textured_wall(t_data *data, t_ray *ray, t_stripe *stripe, t_img *img);
int		get_corresponding_pixel_color(t_stripe *stripe, t_img *texture, double scale);

// +------------------------------------------+ //
//   Functions for mlx manipulation             //
// +------------------------------------------+ //
int		convert_rgb_to_int(int t, int r, int g, int b);
t_img	*generate_new_empty_image(t_data *data, int width, int height);
void    fill_img_buffer(t_data *data, t_img *img, t_ivec *pos, unsigned int pixel_color);
void	bitshifting_depending_on_endian(int endian, t_img *img, unsigned int pixel_color, int pixel_pos);

// +------------------------------------------+ //
//   Functions hooks, shifts and rotations      //
// +------------------------------------------+ //
void	set_hooks(t_data *data);
int     key_press_hook(int keycode, t_data *data);
int     close_win_hook(t_data *data);
void	move(int keycode, t_data *data);
void    move_foward(t_player *player, char **map, t_map *map_info);
void    move_backward(t_player *player, char **map, t_map *map_info);
void    move_right(t_player *player, char **map, t_map *map_info);
void    move_left(t_player *player, char **map, t_map *map_info);
void	rotate(int keycode, t_data *data);
void	rotate_right(t_player *player);
void	rotate_left(t_player *player);

#endif
