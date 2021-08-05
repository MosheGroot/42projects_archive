/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgroot <mgroot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 15:30:30 by mgroot            #+#    #+#             */
/*   Updated: 2021/04/10 11:45:07 by mgroot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "vec_math.h"
# include "list.h"
# include "errors.h"
# include <stdio.h>

typedef unsigned int	t_uint;

/*
 * Objects on scene
*/

typedef struct s_col
{
	t_uint	r;
	t_uint	g;
	t_uint	b;
}			t_col;

typedef struct s_obj
{
	double		(*get_inters_func)();
	t_crd		(*get_normal_func)();
	t_crd		coords[3];
	double		d;
	double		len;
	t_col		col;
}			t_obj;

typedef struct s_cam
{
	t_crd		pos;
	t_crd		dir;
	t_crd		basis_x;
	t_crd		basis_y;
	t_uint		fov;
}			t_cam;

typedef struct s_light
{
	t_crd		pos;
	double		br;
	t_col		col;
}			t_light;

/*
 * Global scene struct
*/

typedef struct s_scene
{
	double		amb_coeff;
	t_col		amb_col;
	t_list		*cams;
	t_list		*lights;
	t_list		*objs;
}			t_scene;

/*
 *MLX & global data structs
*/

typedef struct s_xy_pair
{
	t_uint	x;
	t_uint	y;
}			t_xy_pair;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bps;
	int		line_size;
	int		endian;
}		t_image;

typedef struct s_frame
{
	t_uint			res_x;
	t_uint			res_y;
	t_image			*img;
	t_scene			scene;
	t_list			*curr_cam;
	double			zoom;
	int				rendered;
}			t_frame;

typedef struct s_data
{
	t_frame		frame;
	void		*mlx;
	void		*mlx_win;
}			t_data;

t_col	color_get_default(void);
t_col	color_mul(t_col col, double l);
t_col	color_add(t_col a, t_col b);

#endif