/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgroot <mgroot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 10:51:05 by mgroot            #+#    #+#             */
/*   Updated: 2021/04/10 14:13:54 by mgroot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "scene.h"
# include "vec_math.h"
# include <pthread.h>

# define TH 4

typedef struct s_render_segment
{
	unsigned int	begin_y;
	unsigned int	end_y;
	double			fov_tan;
	t_frame			*frame;
}	t_render_segment;

void	render_frame(t_frame *frame);

t_col	get_pxl_color(t_crd *origin, t_crd *ray, t_scene *scene);
t_crd	cast_ray(t_xy_pair *pixel, t_frame *frame, double fov_tan);
t_obj	*check_intersection(const t_crd *origin, const t_crd *ray,
			const t_list *objs, double *t);
t_light	get_light(t_crd *origin, t_crd normal, const t_scene *scene);

#endif
