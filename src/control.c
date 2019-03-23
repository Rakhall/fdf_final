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

void	description(t_fdf *fdf)
{
	int		y;
	void	*mlx;
	void	*win;

	y = 0;
	mlx = fdf->mlx;
	win = fdf->window;
	mlx_string_put(mlx, win, 65, y += 20, TEXT_COLOR, "Menu:");
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR, "Switch color: V");
	mlx_string_put(mlx, win, 15, y += 20, TEXT_COLOR, "Switch Red: =");
	mlx_string_put(mlx, win, 15, y += 20, TEXT_COLOR, "Switch Green: /");
	mlx_string_put(mlx, win, 15, y += 20, TEXT_COLOR, "Switch Blue: *");
	mlx_string_put(mlx, win, 15, y += 35, TEXT_COLOR, "Zoom: Scroll or +/-");
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR, "Move: Arrows");
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR, "Height: Q/A");
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR, "Rotate:");
	mlx_string_put(mlx, win, 57, y += 25, TEXT_COLOR, "X-Axis - 2/8");
	mlx_string_put(mlx, win, 57, y += 25, TEXT_COLOR, "Y-Axis - 4/6");
	mlx_string_put(mlx, win, 57, y += 25, TEXT_COLOR, "Z-Axis - 7/9");
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR, "Projection:");
	mlx_string_put(mlx, win, 57, y += 25, TEXT_COLOR, "ISO: E");
	mlx_string_put(mlx, win, 57, y += 25, TEXT_COLOR, "Parallel: W");
}

void	rotate_keys(int key, t_fdf *fdf)
{
	if (key == 91)
		fdf->cam->x += 0.05;
	if (key == 84)
		fdf->cam->x -= 0.05;
	if (key == 88)
		fdf->cam->y += 0.05;
	if (key == 86)
		fdf->cam->y -= 0.05;
	if (key == 89)
		fdf->cam->z += 0.05;
	if (key == 92)
		fdf->cam->z -= 0.05;
}

void	projections(int key, t_fdf *fdf)
{
	fdf->cam->x = 0;
	fdf->cam->y = 0;
	fdf->cam->z = 0;
	if (key == 13)
		fdf->map->project = 0;
	if (key == 14)
		fdf->map->project = 1;
}

int		hook_keydown(int key, t_fdf *fdf)
{
	if (key == 13 || key == 14)
		projections(key, fdf);
	rotate_keys(key, fdf);
	if (key == 53)
		exit(EXIT_SUCCESS);
	if (key == 126)
		fdf->cam->offsety -= 5;
	if (key == 125)
		fdf->cam->offsety += 5;
	if (key == 123)
		fdf->cam->offsetx -= 5;
	if (key == 124)
		fdf->cam->offsetx += 5;
	if (key == 69)
		fdf->cam->scale += 1;
	if (key == 78)
		fdf->cam->scale -= fdf->cam->scale < 2 ? 0 : 1;
	if (key == 12)
		fdf->map->z_scale += 1;
	if (key == 0)
		fdf->map->z_scale -= 1;
	if (key == 9 || key == 67 || key == 81 || key == 75)
		switch_color(fdf->map, key);
	render(fdf);
	return (0);
}

int		mouse_scroll(int button, int x, int y, t_fdf *fdf)
{
	(void)x;
	(void)y;
	if (button == 4)
		fdf->cam->scale += 1;
	if (button == 5)
		fdf->cam->scale -= fdf->cam->scale < 2 ? 0 : 1;
	render(fdf);
	return (0);
}
