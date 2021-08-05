/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_math.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgroot <mgroot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 15:30:31 by mgroot            #+#    #+#             */
/*   Updated: 2021/04/10 10:08:16 by mgroot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_MATH_H
# define VEC_MATH_H

# include <math.h>

# define EPS 1e-9

typedef struct s_crd
{
	double	x;
	double	y;
	double	z;
}				t_crd;

t_crd	vec_build(double x, double y, double z);
t_crd	vec_get(t_crd a, t_crd b);

double	vec_module(t_crd vec);
double	vec_dot(t_crd a, t_crd b);

t_crd	vec_cross_prod(t_crd a, t_crd b);
t_crd	vec_mul(t_crd vec, double l);
t_crd	vec_normalize(t_crd vec);
t_crd	vec_sum(t_crd a, t_crd b);

t_crd	point_move_to(t_crd p, t_crd vec);

t_crd	pvec_get(const t_crd *a, const t_crd *b);
double	pvec_module(const t_crd *vec);
double	pvec_dot(const t_crd *a, const t_crd *b);
t_crd	pvec_cross_prod(const t_crd *a, const t_crd *b);

#endif
