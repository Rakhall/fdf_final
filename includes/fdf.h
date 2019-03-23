/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstannis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 08:09:55 by sstannis          #+#    #+#             */
/*   Updated: 2019/02/24 08:09:57 by sstannis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <limits.h>
# include <unistd.h>
# define BUFF_SIZE  	4096
# define WIDTH			1280
# define HEIGHT			720
# define TEXT_COLOR		0xEAEAEA
# define BLUE			0x0000FF
# define RED			0xFF0000
# define GREEN			0x00FF00
# define ORANGE			0xF39C12
# define CIAN			0x117864
# define PURPLE			0x7D3C98
# define BLACK			0x000000

typedef struct		s_cam
{
	double		offsetx;
	double		offsety;
	double		x;
	double		y;
	double		z;
	int			scale;
}					t_cam;

typedef struct		s_vec
{
	double		x;
	double		y;
	double		z;
	int			color;
}					t_vec;

typedef struct		s_map
{
	char			*lmap;
	int				width;
	int				height;
	int				depth_min;
	int				depth_max;
	double			z_scale;
	t_vec			***vecs;
	int				project;
	int				cur_color;
	int				i;
}					t_map;

typedef struct		s_image
{
	void		*image;
	char		*ptr;
	int			bpp;
	int			stride;
	int			endian;
}					t_image;

typedef struct		s_fdf
{
	void		*mlx;
	void		*window;
	t_image		*image;
	t_map		*map;
	t_cam		*cam;
	double		**zbuf;
}					t_fdf;

typedef struct		s_line
{
	t_vec		start;
	t_vec		stop;
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			err;
	int			err2;
}					t_line;

int					valider(t_map *map, unsigned i, int j, unsigned size);
int					writer(t_map *map, int i, int y, int x);
int					ft_atoi_base(const char *str, int str_base);
void				put_color(t_map *map, int colour);
int					get_color(int c1, int c2, double p);
double				gradient(double val, double first, double second);
t_fdf				*init(char *title, t_map *map);
t_image				*new_image(t_fdf *fdf);
t_image				*del_image(t_fdf *fdf, t_image *img);
void				render(t_fdf *fdf);
int					put_points(t_fdf *fdf, t_line *l, t_vec *p1,
t_vec *p2);
void				image_set_pixel(t_image *image, int x, int y, int color);
int					mouse_scroll(int button, int x, int y, t_fdf *mlx);
int					hook_keydown(int key, t_fdf *fdf);
void				description(t_fdf *fdf);
void				switch_color(t_map *map, int key);
void				rgb(t_map *map, int key);
void				error(void);
#endif
