/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 11:15:48 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/24 12:02:31 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line(char **line)
{
	int		i;
	int		ret;
	char	buffer;

	if (line == NULL)
		return (-1);
	*line = malloc(1234567);
	if (*line == NULL)
		return (-1);
	i = 0;
	while ((ret = read(0, &buffer, 1)) != 0 && buffer != '\n')
	{
		if (ret == -1)
			return (-1);
		(*line)[i++] = buffer;
	}
	(*line)[i++] = '\0';
	if (buffer == '\n')
		return (1);
	return (0);
}
