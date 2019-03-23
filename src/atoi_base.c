/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnienow <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 13:39:28 by mnienow           #+#    #+#             */
/*   Updated: 2019/03/15 13:39:32 by mnienow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_iswhitespace(char const c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\v'
	|| c == '\r' || c == '\f')
		return (1);
	return (0);
}

int		base(int c, int base)
{
	char	*str;
	char	*str2;
	int		i;

	i = 0;
	str = "0123456789abcdefx";
	str2 = "0123456789ABCDEFX";
	while (i < base)
	{
		if (c == str[16] || c == str2[16])
			return (0);
		if (c == str[i] || c == str2[i])
			return (i);
		i++;
	}
	return (-1);
}

int		ft_atoi_base(const char *str, int str_base)
{
	int		nb;
	int		sign;
	int		i;

	nb = 0;
	sign = 0;
	i = 0;
	while (ft_iswhitespace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = 1;
		i++;
	}
	while (base(str[i], str_base) != -1)
	{
		nb = nb * str_base;
		nb = nb + base(str[i], str_base);
		i++;
	}
	if (sign)
		return (-nb);
	return (nb);
}

void	rgb(t_map *map, int key)
{
	int		col;

	col = map->cur_color;
	if (key == 75)
		map->cur_color = ((col << 16) >> 24) < 255 ? map->cur_color
		+ 0x000100 : 0x000000;
	if (key == 67)
		map->cur_color += ((col << 16) >> 16) < 255 ? 1 : -255;
	if (key == 81)
		map->cur_color = (col >> 16) < 255 ? (((col >> 16) + 1)
		<< 16) | ((col << 16) >> 16) : 0 | ((col << 16) >> 16);
	put_color(map, map->cur_color);
}
