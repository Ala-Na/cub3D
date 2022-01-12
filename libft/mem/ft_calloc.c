/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 00:01:34 by anadege           #+#    #+#             */
/*   Updated: 2022/01/12 15:26:49 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*ptr;
	unsigned char	*res;
	size_t			total;

	total = nmemb * size;
	if (!(total))
		total = 1;
	ptr = malloc(total);
	if (!ptr)
		return (NULL);
	res = (unsigned char *)ptr;
	while (total > 0)
	{
		*res++ = '\0';
		total--;
	}
	return (ptr);
}
