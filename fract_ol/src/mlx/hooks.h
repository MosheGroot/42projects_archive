#ifndef HOOKS_H
# define HOOKS_H

# include "window.h"

int   key_hook_func(int key, t_data *data);

int   mouse_click_hook_func(int button, int x, int y, t_data *data);

int   mouse_move_hook_func(int x, int y, t_data *data);

#endif //!HOOKS_H