/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:22:43 by fmonbeig          #+#    #+#             */
/*   Updated: 2022/01/10 15:52:29 by anadege          ###   ########.fr       */
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

# include "../libft/libft.h"
# include "mlx.h"

// +------------------------------------------+ //
//   Structure                                  //
// +------------------------------------------+ //

typedef struct s_data
{
	void		*mlx;
	char		**map;
	t_map		map_info;
	t_texture	texture;

}				t_data;

typedef struct s_map
{
	char		height;
	char		width;
	char		player_orientation;
	float		player_height;
	float		player_width;
}				t_map;
typedef struct s_texture
{
	char	*no_file;
	char	*so_file;
	char	*we_file;
	char	*ea_file;
	char	**f_file;
	char	**c_file;
	t_img	*no;
	t_img	*so;
	t_img	*we;
	t_img	*ea;

}				t_texture;

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_img;

// +------------------------------------------+ //
//   Define                                     //
// +------------------------------------------+ //
# define BUFFER_SIZE 		10
# define ERROR_NAME_MAP 	"ERROR: bad map extension\n"
# define ERROR_NB_ARGUMENT	"ERROR: wrong number of argument\n"
# define ERROR_GNL			"ERROR: bad read of the file\n"
# define ERROR_ELEMENT		"ERROR: Element are missing or are incorrect\n"
//TODO => Define les touches de clavier sur linux

// +------------------------------------------+ //
//   Check file                                  //
// +------------------------------------------+ //
void	check_file(char *map, t_data *data);

// +------------------------------------------+ //
//   Parsing                                    //
// +------------------------------------------+ //

// +------------------------------------------+ //
//   ERROR and FREE                             //
// +------------------------------------------+ //
void	ft_error(char *str, t_data *data);
void	ft_error_during_gnl(char *error_message, int fd, char *line, t_data *data);
void	free_everything(t_data *data);

// +------------------------------------------+ //
//   GNL                            //
// +------------------------------------------+ //

int		get_next_line(int fd, char **line, int flag);
char	*ft_strjoin_get_next_line(const char *s1, const char *s2);


#endif

