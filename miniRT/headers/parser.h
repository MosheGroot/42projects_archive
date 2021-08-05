#ifndef PARSER_H
# define PARSER_H

# include <unistd.h>
# include <fcntl.h>
# include "errors.h"
# include "get_next_line.h"
# include "scene.h"
# include "norm_utilities.h"

/*	parser	*/
void			parse_file(char *filename, t_data *data);

/*	parser2	*/
void			emergency_quit(int r_status, int p_status, t_scene *data);
int				emergency_return_n_free(void *to_free, int code);

int				parse_resolution(char *command, t_frame *data);
int				parse_ambient_light(char *command, t_scene *data);
int				parse_camera(char *command, t_scene *data);
int				parse_light(char *command, t_scene *data);
int				parse_sphere(char *command, t_scene *data);
int				parse_plane(char *command, t_scene *data);
int				parse_square(char *command, t_scene *data);
int				parse_triangle(char *command, t_scene *data);
int				parse_cylinder(char *command, t_scene *data);

/*	utils	*/
int				get_t_uinteger(unsigned int *num, char *command);
int				get_3t_uinteger(unsigned int *a, unsigned int *b,
					unsigned int *c, char *command);
int				get_float(double *num, char *command);
int				get_3float(double *a, double *b, double *c, char *command);

/*	ato_funcs	*/
unsigned int	ft_atoui(const char *str, int *res_shift);
double			ft_atof(const char *str, int *res_shift);
int				ft_isdigit(char c);
int				ft_isspace(char c);

#endif
