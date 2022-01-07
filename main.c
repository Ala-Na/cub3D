/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:21:33 by fmonbeig          #+#    #+#             */
/*   Updated: 2022/01/07 18:03:16 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	init_data(t_data *data)
{
	data->map_info.player_orientation = 0;
	data->map_info.player_height = 0;
	data->map_info.player_width = 0;
}

int	main(int argc, char **argv)
{
	t_data data;

	if (argc == 2)
	{
		init_data(&data);
		check_file(argv[1], &data);
	}
	else
		ft_putstr(ERROR_NB_ARGUMENT);
	return (0);
}

//	perror("ERROR"); Permet de prnt avec ERROR au debut
//	utiliser une liste chainée pour stocker tous nos malloc ? // on utilise un calloc dans lequel on copie l'adresse du pointeur dans une liste chainée afin de tout free a la fin.
//	Est ce qu on utilise un type def t_bool pour les fonctions booleenne ?
//	Est ce qu on utilise calloc au lieu de malloc ?
