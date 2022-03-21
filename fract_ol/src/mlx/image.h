#ifndef IMAGE_H
# define IMAGE_H

# include <inttypes.h>

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bps;
	int		line_size;
	int		endian;
}	t_image;

void		image_put_pixel(t_image *img, uint32_t x, uint32_t y,
				uint32_t color);

#endif //!IMAGE_H