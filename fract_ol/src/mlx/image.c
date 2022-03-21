#include "image.h"

void	image_put_pixel(t_image *img, uint32_t x, uint32_t y,
			unsigned int color)
{
	char	*dest;

	dest = img->addr + (img->line_size * y + img->bps * x / 8);
	*(unsigned int *)dest = color;
}
