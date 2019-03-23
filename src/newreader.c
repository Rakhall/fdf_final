/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newreader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnienow <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 18:04:17 by mnienow           #+#    #+#             */
/*   Updated: 2019/03/18 18:04:20 by mnienow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_fdf	*fdfdel(t_fdf *fdf)
{
	if (fdf->window != NULL)
		mlx_destroy_window(fdf->mlx, fdf->window);
	if (fdf->cam != NULL)
		ft_memdel((void **)&fdf->cam);
	if (fdf->image != NULL)
		del_image(fdf, fdf->image);
	ft_memdel((void **)&fdf);
	return (NULL);
}

t_fdf			*init(char *title, t_map *map)
{
	t_fdf	*fdf;

	if ((fdf = ft_memalloc(sizeof(t_fdf))) == NULL)
		return (NULL);
	if ((fdf->mlx = mlx_init()) == NULL ||
	(fdf->window = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, title)) == NULL ||
	(fdf->cam = ft_memalloc(sizeof(t_cam))) == NULL ||
	((fdf->image = new_image(fdf)) == NULL))
		return (fdfdel(fdf));
	fdf->cam->scale = 31;
	fdf->cam->offsetx = WIDTH / 2;
	fdf->cam->offsety = HEIGHT / 2;
	if ((map->width * fdf->cam->scale) > (WIDTH / 3 * 2) ||
	(map->height * fdf->cam->scale) > (HEIGHT / 3 * 2))
	{
		while ((map->width * fdf->cam->scale) > (WIDTH / 3 * 2)
		&& fdf->cam->scale > 1)
			fdf->cam->scale--;
		while ((map->height * fdf->cam->scale) > (HEIGHT / 3 * 2)
		&& fdf->cam->scale > 1)
			fdf->cam->scale--;
	}
	return (fdf);
}

static t_vec	*new_vec(int j, int k, int *i, t_map *map)
{
	t_vec		*new;

	new = (t_vec *)malloc(sizeof(t_vec));
	new->x = k;
	new->y = j;
	new->z = ft_atoi(&map->lmap[*i]);
	map->depth_min = new->z < map->depth_min ? new->z : map->depth_min;
	map->depth_max = new->z > map->depth_max ? new->z : map->depth_max;
	while (map->lmap[*i] >= '0' && map->lmap[*i] <= '9')
		i[0]++;
	if (map->lmap[*i] == ',')
	{
		i[0]++;
		new->color = ft_atoi_base(&map->lmap[*i], 16);
		while (map->lmap[*i] != 32 && map->lmap[*i] && map->lmap[*i] != 10)
			i[0]++;
		map->cur_color = 0;
	}
	else
		new->color = 0;
	return (new);
}

int				writer(t_map *map, int i, int y, int x)
{
	map->depth_min = 0;
	if (!(map->vecs = (t_vec ***)malloc(sizeof(t_vec **) * map->height)))
		return (-1);
	while (i <= map->height)
		if (!(map->vecs[i++] = (t_vec **)malloc(sizeof(t_vec *) * map->width)))
			return (-1);
	i = 0;
	while (map->lmap[i])
	{
		if (map->lmap[i] >= '0' && map->lmap[i] <= '9')
		{
			map->vecs[y][x] = new_vec(y, x, &i, map);
			x += x < map->width ? 1 : 0;
		}
		if (map->lmap[i] == '\n')
		{
			y++;
			x = 0;
		}
		i++;
	}
	free(map->lmap);
	map->lmap = 0;
	put_color(map, BLUE);
	return (0);
}

int				valider(t_map *map, unsigned i, int j, unsigned size)
{
	while (map->lmap[i] && --size)
	{
		while (map->lmap[i] == ' ')
			i++;
		if (map->lmap[i] >= 48 && map->lmap[i] <= 57)
		{
			while (map->lmap[i] >= 48 && map->lmap[i] <= 57)
				i++;
			map->width += map->height ? 0 : 1;
			j++;
		}
		if (map->lmap[i] == ',')
			while ((map->lmap[i] >= 48 && map->lmap[i] <= 57) || (map->lmap[i]
			>= 65 && map->lmap[i] <= 70) || (map->lmap[i] >= 97 &&
			map->lmap[i] <= 102) || map->lmap[i] == 'x' || map->lmap[i] == 'X'
			|| map->lmap[i] == ',')
				i++;
		if (map->lmap[i] == '\n')
			if (map->width != j)
				error();
		map->lmap[i] == '\n' ? j = 0 : 0;
		map->lmap[i] == '\n' ? map->height += 1 : 0;
		map->lmap[i] == '\n' ? i += 1 : 0;
	}
	return (size);
}
