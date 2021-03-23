/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 17:23:30 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/23 19:58:21 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"

int		ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strnchr(char *str, char chr, int len)
{
	int	i;

	i = 0;
	while (str[i] && i < len)
	{
		if (str[i] == (unsigned char)chr)
			return ((char*)&str[i]);
		i++;
	}
	if (i < len && (unsigned char)chr == '\0')
		return ((char*)&str[i]);
	return (NULL);
}

int		main(int argc, char **argv)
{
	int		i;
	int		len;
	char	*str;

	if (argc != 3)
	{
		write(1, "\n", 1);
		return (1);
	}
	i = -1;
	str = argv[1];
	len = ft_strlen(argv[2]);
	while (str[++i])
	{
		if (ft_strnchr(str, str[i], i) != NULL ||
				ft_strnchr(argv[2], str[i], len) == NULL)
			continue ;
		write(1, &str[i], 1);
	}
	write(1, "\n", 1);
	return (0);
}
