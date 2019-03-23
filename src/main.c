/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstannis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 07:24:29 by sstannis          #+#    #+#             */
/*   Updated: 2019/02/24 07:24:31 by sstannis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			error(void)
{
	write(1, "error\n", 6);
	exit(0);
}

char			*readjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*a;

	i = 0;
	j = 0;
	if (!s1 || !s2 || !(a = (char*)malloc(sizeof(char)
					* (ft_strlen(s2) + ft_strlen(s1)) + 1)))
		return (NULL);
	while (s1[i])
	{
		a[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		a[i] = s2[j];
		i++;
		j++;
	}
	a[i] = '\0';
	free(s1);
	return (a);
}

static int		reader(int fd, t_map *map)
{
	char	buf[BUFF_SIZE + 1];
	int		ret;

	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret < 0)
			return (-1);
		map->depth_min += ret;
		buf[ret] = '\0';
		map->lmap = readjoin(map->lmap, buf);
	}
	return (0);
}

static t_map	*new_map(void)
{
	t_map	*map;

	map = ft_memalloc(sizeof(t_map));
	if (map == NULL)
		return (NULL);
	map->lmap = ft_strnew(1);
	map->width = 0;
	map->height = 0;
	map->depth_min = 0;
	map->depth_max = 1;
	map->z_scale = 3;
	map->project = 0;
	map->i = 0;
	map->cur_color = 1;
	return (map);
}

int				main(int argc, char **argv)
{
	t_map	*map;
	t_fdf	*fdf;
	int		fd;

	if (argc != 2)
		return (0);
	fd = open(argv[1], O_RDONLY);
	map = new_map();
	if (fd < 0 || reader(fd, map))
		error();
	if (!(valider(map, 0, 0, map->depth_min)) || writer(map, 0, 0, 0))
		error();
	if ((fdf = init("My awesome fdf", map)) == NULL)
		error();
	fdf->map = map;
	render(fdf);
	mlx_hook(fdf->window, 2, 0, hook_keydown, fdf);
	mlx_hook(fdf->window, 4, 0, mouse_scroll, fdf);
	mlx_loop(fdf->mlx);
	return (0);
}
