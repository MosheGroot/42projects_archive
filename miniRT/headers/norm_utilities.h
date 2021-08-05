/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_utilities.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgroot <mgroot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 10:27:50 by mgroot            #+#    #+#             */
/*   Updated: 2021/04/10 11:38:38 by mgroot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NORM_UTILITIES_H
# define NORM_UTILITIES_H

# include "scene.h"

t_uint	uint_ternary(int result, t_uint true_v, t_uint false_v);
int		int_ternary(int result, int true_v, int false_v);
double	double_ternary(int result, double true_v, double false_v);

int		int_assigment(int *dest, int value);
void	*void_ptr_assigment(void **dest, void *value);

#endif