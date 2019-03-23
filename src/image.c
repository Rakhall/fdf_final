/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstannis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 07:24:29 by sstannis          #+#    #+#             */
/*   Updated: 2019/03/23 20:20:44 by sstannis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		image_set_pixel(t_image *image, int x, int y, int color)
{
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	*(int *)(image->ptr + ((x + y * WIDTH) * image->bpp)) = color;
}

t_image		*del_image(t_fdf *fdf, t_image *img)
{
	if (img != NULL)
	{
		if (img->image != NULL)
			mlx_destroy_image(fdf->mlx, img->image);
		ft_memdel((void **)&img);
	}
	return (NULL);
}

t_image		*new_image(t_fdf *fdf)
{
	t_image		*img;

	if ((img = ft_memalloc(sizeof(t_image))) == NULL)
		return (NULL);
	if ((img->image = mlx_new_image(fdf->mlx, WIDTH, HEIGHT)) == NULL)
		return (del_image(fdf, img));
	img->ptr = mlx_get_data_addr(img->image, &img->bpp, &img->stride,
			&img->endian);
	img->bpp /= 8;
	return (img);
}

int			put_points(t_fdf *fdf, t_line *l, t_vec *p1,
		t_vec *p2)
{
	double	percent;

	percent = (l->dx > l->dy ?
			gradient((int)p1->x, (int)l->start.x, (int)l->stop.x)
			: gradient((int)p1->y, (int)l->start.y, (int)l->stop.y));
	image_set_pixel(fdf->image, (int)p1->x, (int)p1->y, get_color(p1->color,
				p2->color, percent));
	l->err2 = l->err;
	if (l->err2 > -l->dx)
	{
		l->err -= l->dy;
		p1->x += l->sx;
	}
	if (l->err2 < l->dy)
	{
		l->err += l->dx;
		p1->y += l->sy;
	}
	return (0);
}
