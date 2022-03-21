#include "colors.h"

#include <math.h>

static t_col	set_colorset_galactic(int iteration, int max_iteration)
{
	t_col	col;
	double	t;

	if (iteration >= max_iteration)
	{
		col.r = 30;
		col.g = 0;
		col.b = 0;
	}
	else
	{	
		t = (double)iteration / (double)(1 + max_iteration);
		col.r = (int)(9 * (1 - t) * pow(t, 3) * 255);
		col.g = (int)(15 * pow((1 - t), 2) * pow(t, 2) * 255);
		col.b = (int)(8.5 * pow((1 - t), 3) * t * 255);
	}
	return (col);
}

static t_col	set_colorset_red(int iteration, int max_iteration)
{
	t_col	col;

	if (iteration >= max_iteration)
	{
		col.r = 141;
		col.g = 26;
		col.b = 187;
	}
	else
	{
		col.r = (iteration * 12) % 255;
		col.g = (iteration * 0) % 255;
		col.b = (iteration * 6) % 255;
	}
	return (col);
}

static t_col	set_colorset_psycho(int iteration, int max_iteration)
{
	t_col	col;

	if (iteration >= max_iteration)
	{
		col.r = 20;
		col.g = 0;
		col.b = 80;
	}
	else
	{
		col.r = (iteration * 128) % 255;
		col.g = (iteration * 255) % 255;
		col.b = (iteration * 64) % 255;
	}
	return (col);
}

t_col	get_fractal_color(enum e_colorset colorset, int iteration,
			int max_iteration)
{
	t_col	color;

	color.r = 0;
	color.g = 0;
	color.b = 0;
	if (colorset == colorset_galactic)
		color = set_colorset_galactic(iteration, max_iteration);
	else if (colorset == colorset_red)
		color = set_colorset_red(iteration, max_iteration);
	else if (colorset == colorset_psycho)
		color = set_colorset_psycho(iteration, max_iteration);
	return (color);
}

uint32_t	color_to_ui(t_col color)
{
	color.r = (color.r > 255) ? 255 : color.r;
	color.g = (color.g > 255) ? 255 : color.g;
	color.b = (color.b > 255) ? 255 : color.b;
	return ((color.r << 16) + (color.g << 8) + color.b);
}
