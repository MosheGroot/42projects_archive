/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgroot <mgroot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 13:12:10 by mgroot            #+#    #+#             */
/*   Updated: 2021/04/10 11:28:56 by mgroot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include <mlx.h>
# include "render.h"

# define TITLE	"title"

void	start_window(t_data *data);

void	put_pixel(t_image *img, t_xy_pair *pixel, t_uint color);
t_uint	t_col_to_ui(t_col *color);

void	switch_zoom(int key, t_frame *frame);
void	switch_cam(int key, t_frame *frame);
int		close_window(t_data *params);

void	save_to_file(t_data *data, const char *filename);

#endif