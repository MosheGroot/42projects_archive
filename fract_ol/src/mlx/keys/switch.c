#include "keys.h"

int	is_switch_set_keyboard_key(int key)
{
	return (key == KEY_Q || key == KEY_E);
}

void	switch_set(int key, t_frame *frame)
{
	if (key == KEY_Q)
	{
		if (frame->set != FRACTOL_SET_NUMBER_MIN)
			frame->set -= 1;
		else
			frame->set = FRACTOL_SET_NUMBER_MAX;
	}
	else if (key == KEY_E)
	{
		if (frame->set != FRACTOL_SET_NUMBER_MAX)
			frame->set += 1;
		else
			frame->set = FRACTOL_SET_NUMBER_MIN;
	}
	frame->rendered = 0;
}

int	is_switch_colorset_keyboard_key(int key)
{
	return (key == KEY_ONE || key == KEY_TWO || key == KEY_THREE);
}

void	switch_colorset(int key, t_frame *frame)
{
	if (key == KEY_ONE)
		frame->colorset = (enum e_colorset)(1);
	else if (key == KEY_TWO)
		frame->colorset = (enum e_colorset)(2);
	else if (key == KEY_THREE)
		frame->colorset = (enum e_colorset)(3);
	frame->rendered = 0;
}
