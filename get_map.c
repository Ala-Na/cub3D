/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 17:35:08 by fmonbeig          #+#    #+#             */
/*   Updated: 2022/01/10 18:44:31 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// Map limit = MAP_LIMIT * MAP_LIMIT
// la map sera rempli de /0

static void	malloc_map(int fd, char *line, t_data *data)
{
	int	i;

	i = -1;
	if (!data->map)
		data->map = ft_calloc(MAP_LIMIT, sizeof(char *));
	if (!data->map)
		ft_error_during_gnl(ERROR_MALLOC, fd, line, data);
	while (++i < MAP_LIMIT)
		data->map[i] = ft_calloc(MAP_LIMIT, sizeof(char));
}

static void	replace_white_space(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if(ft_iswhitespace(line[i]))
			line[i] = 1;
}

static void	check_first_line(int fd, char *line, t_data *data)
{
	int	i;

	i = -1;
	while(line[++i])
		if (line[i] != 1)
			ft_error_during_gnl(ERROR_MAP_IS_TO_BIG, fd, line, data);
}


void	get_map(int fd, char *line, t_data *data)
{
	static int	i = 0;
	int			j;

	j = -1;
	malloc_map(fd, line, data);
	replace_white_space(line);
	if (i == 0)
		check_first_line(fd,line, data);
	// la ligne 1 ne doit contenir que des 1
	// les lignes doivent commencer par 1 et finir par 1
	// test de ligne on peut checker les chiffres et lettres interdites
	while(line[++j])
	{
		data->map[i][j] = line[j];
		if (i == MAP_LIMIT || j == MAP_LIMIT)
			ft_error_during_gnl(ERROR_MAP_IS_TO_BIG, fd, line, data);
	}
	i++;
	//avec les /0 on peut faire un algo qui test chaque point de la map pour savoir si elle est ouverte ou fermé // le faire apres les tests preliminaires
}
