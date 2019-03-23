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

void		line(t_fdf *fdf, t_vec p1, t_vec p2)
{
	t_line	line;

	p1.x = (int)p1.x;
	p2.x = (int)p2.x;
	p1.y = (int)p1.y;
	p2.y = (int)p2.y;
	line.start = p1;
	line.stop = p2;
	line.dx = (int)ft_abs((int)p2.x - (int)p1.x);
	line.sx = (int)p1.x < (int)p2.x ? 1 : -1;
	line.dy = (int)ft_abs((int)p2.y - (int)p1.y);
	line.sy = (int)p1.y < (int)p2.y ? 1 : -1;
	line.err = (line.dx > line.dy ? line.dx : -line.dy) / 2;
	while (((int)p1.x != (int)p2.x || (int)p1.y != (int)p2.y))
		if (put_points(fdf, &line, &p1, &p2))
			break ;
}

t_vec		matrix(t_vec p, t_cam *camera)
{
	double		x;
	double		y;

	x = p.x;
	p.x = cos(camera->y) * x + sin(camera->y) * p.z;
	p.z = -sin(camera->y) * x + cos(camera->y) * p.z;
	y = p.y;
	p.y = cos(camera->x) * y - sin(camera->x) * p.z;
	p.z = sin(camera->x) * y + cos(camera->x) * p.z;
	x = p.x;
	y = p.y;
	p.x = cos(camera->z) * x - sin(camera->z) * y;
	p.y = sin(camera->z) * x + cos(camera->z) * y;
	return (p);
}

static void	iso(double *x, double *y, int z)
{
	int previous_x;
	int previous_y;

	previous_x = (int)*x;
	previous_y = (int)*y;
	*x = (previous_x - previous_y) * cos(0.523599);
	*y = -z + (previous_x + previous_y) * sin(0.523599);
}

t_vec		project(t_vec v, t_fdf *fdf)
{
	v.x -= (double)(fdf->map->width - 1) / 2.0f;
	v.y -= (double)(fdf->map->height - 1) / 2.0f;
	v.z *= fdf->map->z_scale;
	v.x *= fdf->cam->scale;
	v.y *= fdf->cam->scale;
	v = matrix(v, fdf->cam);
	if (fdf->map->project)
		iso(&v.x, &v.y, (int)v.z);
	v.x += fdf->cam->offsetx;
	v.y += fdf->cam->offsety;
	return (v);
}

void		render(t_fdf *fdf)
{
	int			x;
	int			y;

	ft_bzero(fdf->image->ptr, WIDTH * HEIGHT * fdf->image->bpp);
	x = 0;
	while (x < fdf->map->width)
	{
		y = 0;
		while (y < fdf->map->height)
		{
			if (x + 1 < fdf->map->width)
				line(fdf, project(*fdf->map->vecs[y][x], fdf),
				project(*fdf->map->vecs[y][x + 1], fdf));
			if (y + 1 < fdf->map->height)
				line(fdf, project(*fdf->map->vecs[y][x], fdf),
				project(*fdf->map->vecs[y + 1][x], fdf));
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->image->image, 0, 0);
	description(fdf);
}
