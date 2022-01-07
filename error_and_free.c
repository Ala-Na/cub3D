/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:43:15 by fmonbeig          #+#    #+#             */
/*   Updated: 2022/01/07 15:28:41 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/***
 * ft_error : send a error message and exit the program properly.
 * 			if NULL is pass to error_message, we use perror instead.
***/

void	ft_error(char *error_message, t_data *data)
{
	if (!error_message)
		perror("ERROR");
	else
		write(2, error_message, ft_strlen(error_message));
	// TODO : ajouter la fonction qui free tout
}

void	ft_error_during_gnl(char *error_message, int fd, char *line, t_data *data)
{
	get_next_line(fd, &line, 1);
	if (!error_message)
		perror("ERROR");
	else
		write(2, error_message, ft_strlen(error_message));
	// TODO : ajouter la fonction qui free tout
}

void	free_everything(t_data *data)
{
	// TODO : A completer au fur et a mesure avec les mallocs
}
