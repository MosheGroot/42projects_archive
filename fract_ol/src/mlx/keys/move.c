#include "keys.h"

int	is_move_keyboard_key(int key)
{
	return (key == KEY_ARROW_UP
		|| key == KEY_ARROW_DOWN
		|| key == KEY_ARROW_RIGHT
		|| key == KEY_ARROW_LEFT
		|| key == KEY_W
		|| key == KEY_A
		|| key == KEY_S
		|| key == KEY_D);
}

void	move_origin_by_keyboard(int key, t_frame *frame)
{
	static const int	move_delta = 100;

	if (key == KEY_ARROW_UP || key == KEY_W)
		frame->origin.y -= move_delta / frame->zoom;
	else if (key == KEY_ARROW_DOWN || key == KEY_S)
		frame->origin.y += move_delta / frame->zoom;
	else if (key == KEY_ARROW_RIGHT || key == KEY_D)
		frame->origin.x += move_delta / frame->zoom;
	else if (key == KEY_ARROW_LEFT || key == KEY_A)
		frame->origin.x -= move_delta / frame->zoom;
	frame->rendered = 0;
}

int	is_move_mouse_button(int key)
{
	return (key == MOUSE_KEY_LEFT);
}

void	move_origin_by_mouse(int x, int y, t_frame *frame)
{
	frame->origin.x += ((long double)x - frame->res_x / 2) / frame->zoom;
	frame->origin.y += ((long double)y - frame->res_y / 2) / frame->zoom;
	frame->rendered = 0;
}
