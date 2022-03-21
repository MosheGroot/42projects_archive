#ifndef COLORS_H
# define COLORS_H

# include <inttypes.h>

/* COLOR DEFINES */
# define COLOR_WHITE	0xFFFFFF
# define COLOR_RED		0xFF0000

typedef struct s_col
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;
}	t_col;

enum e_colorset
{
	colorset_galactic = 1,
	colorset_red,
	colorset_psycho
};

t_col		get_fractal_color(enum e_colorset colorset, int iteration,
				int max_iteration);

uint32_t	color_to_ui(const t_col color);

#endif //!COLORS_H