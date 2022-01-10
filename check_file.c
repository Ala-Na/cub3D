/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 16:03:42 by fmonbeig          #+#    #+#             */
/*   Updated: 2022/01/07 18:36:23 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	check_extension(char *file, t_data *data)
{
	int	i;

	i = 0;
	while *file[i])
		i++;
	if *file[--i] != 'b')
		ft_error(ERROR_NAME_MAP,data);
	if (file[--i] != 'u')
		ft_error(ERROR_NAME_MAP,data);
	if (file[--i] != 'c')
		ft_error(ERROR_NAME_MAP,data);
	if (file[--i] != '.')
		ft_error(ERROR_NAME_MAP,data);
	if (ft_strlen(file) <= 4)
		ft_error(ERROR_NAME_MAP,data);
}

static t_bool get_element(char *line)
{
	int	i;

	i = -1;
	while(line[++i])
	{
		if (!ft_strncmp(line, "NO", 3))
			ft_strdup(line[])
		if (!ft_strncmp(line, "NO", 3))
			ft_strdup()
		else
			// est ce que tout a été rempli ? si oui alors ok, sinon FAUX
			//NOTA BENE pour le f et le c il faut split sur , puis check s'il n y a que 3 char * puis atoi dans un int **
	}
	return (1);
}

void	check_file(char *file, t_data *data)
{
	int		fd;
	int		ret;
	char	*line;

	ret = 1;
	check_extension(file, data);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_error(NULL, data);
	while (ret)
	{
		ret = get_next_line(fd, &line, 0);
		if (ret == -1)
			ft_error_during_gnl(ERROR_GNL, fd, line, data);
		if (!get_element)
			ft_error_during_gnl(ERROR_ELEMENT, fd, line, data);
		//on s occupe de la map
		free(line);
		line = NULL;
	}
}

//TODO fonction get_map, pour la put dans un char ** (a faire apres avec un second gnl)
//Permet d'obtenir des infos sur la taille de la map par exemple

// doit recuperer d'abord les 6 infos essentielles sinon quit