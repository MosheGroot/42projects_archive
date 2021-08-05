/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgroot <mgroot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 10:00:56 by mgroot            #+#    #+#             */
/*   Updated: 2021/04/10 09:59:45 by mgroot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_H
# define BMP_H

/*
 *	BMP file header structure
 *	
 *	Size of file
 *	Reserved
 *	...
 *	Offset to bitmap data
*/

typedef struct s_bitmap_fileheader
{
	unsigned int	bf_filesize;
	unsigned short	bf_reserved1;
	unsigned short	bf_reserved2;
	unsigned int	bf_offs_bits;
}	t_bitmap_fileheader;

/* 
 *	BMP file info structure
 *	
 *	Size of info header 
 *	Width of image 
 *	Height of image 
 *	Number of color planes 
 *	Number of bits per pixel 
 *	Type of compression to use 
 *	Size of image data 
 *	X pixels per meter 
 *	Y pixels per meter 
 *	Number of colors used 
 *	Number of important colors
*/

typedef struct s_bitmap_infoheader
{
	unsigned int	bi_size;
	int				bi_width;
	int				bi_height;
	unsigned short	bi_planes;
	unsigned short	bi_bps;
	unsigned int	bi_compression;
	unsigned int	bi_image_size;
	int				bi_x_pxs_per_meter;
	int				bi_y_pxs_per_meter;
	unsigned int	bi_colors_used;
	unsigned int	bi_colors_important;
}	t_bitmap_infoheader;

void	prepare_bmp_file(int fd, t_data *data);

#endif