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

void		switch_color(t_map *map, int key)
{
	int		color[7];

	if (key == 9)
	{
		color[0] = RED;
		color[1] = GREEN;
		color[2] = ORANGE;
		color[3] = PURPLE;
		color[4] = BLACK;
		color[5] = CIAN;
		color[6] = BLUE;
		if (map->i == 7)
		{
			map->i = 0;
		}
		put_color(map, color[map->i]);
		map->i++;
	}
	if (key == 67 || key == 81 || key == 75)
		rgb(map, key);
}

static int	get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int			get_color(int c1, int c2, double p)
{
	int red;
	int green;
	int blue;

	if (c1 == c2)
		return (c1);
	red = get_light((c1 >> 16) & 0xFF, (c2 >> 16) & 0xFF, p);
	green = get_light((c1 >> 8) & 0xFF, (c2 >> 8) & 0xFF, p);
	blue = get_light(c1 & 0xFF, c2 & 0xFF, p);
	return (red << 16 | green << 8 | blue);
}

double		gradient(double val, double first, double second)
{
	if (val == first)
		return (0.0);
	if (val == second)
		return (1.0);
	return ((val - first) / (second - first));
}

void		put_color(t_map *map, int colour)
{
	int	y;
	int	x;

	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
			if ((!map->vecs[y][x]->color ||
			map->vecs[y][x]->color == map->cur_color ||
			get_color(map->cur_color, 0xFFFFFF, gradient(map->vecs[y][x]->z,
			map->depth_min, map->depth_max))) && map->cur_color)
				map->vecs[y][x]->color = get_color(colour, 0xFFFFFF,
				gradient(map->vecs[y][x]->z, map->depth_min, map->depth_max));
	}
	map->cur_color = colour;
}
