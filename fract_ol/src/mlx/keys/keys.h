#ifndef KEYS_H
# define KEYS_H

# include "../window.h"

# define KEY_ARROW_UP   126
# define KEY_ARROW_DOWN   125
# define KEY_ARROW_RIGHT  124
# define KEY_ARROW_LEFT   123

# define KEY_A    0
# define KEY_S    1
# define KEY_D    2
# define KEY_Z    6
# define KEY_X    7
# define KEY_W    13
# define KEY_Q    12
# define KEY_E    14
# define KEY_ONE  18
# define KEY_TWO  19
# define KEY_THREE  20
# define KEY_ESC  53
# define KEY_CTRL 256

# define KEY_PLUS  24
# define KEY_MINUS 27
# define KEY_NUM_PLUS  69
# define KEY_NUM_MINUS 78

# define MOUSE_KEY_LEFT   1
# define MOUSE_KEY_RIGHT  2
# define MOUSE_KEY_MIDDLE 3
# define MOUSE_WHEEL_UP   4
# define MOUSE_WHEEL_DOWN 5

/*  KEYBOARD KEYS */
int   is_move_keyboard_key(int key);
void  move_origin_by_keyboard(int key, t_frame *frame);

int   is_switch_set_keyboard_key(int key);
void  switch_set(int key, t_frame *frame);

int   is_switch_colorset_keyboard_key(int key);
void  switch_colorset(int key, t_frame *frame);

int   is_change_depth_keyboard_key(int key);
void  change_depth(int key, t_frame *frame);

int   is_interactive_mode_keyboard_key(int key);
void  change_interactive_mode(int key, t_data *frame);

int   is_zoom_keyboard_key(int key);
void  switch_zoom_by_keyboard(int key, t_frame *frame);


/*   MOUSE  KEYS  */
int   is_move_mouse_button(int key);
void  move_origin_by_mouse(int x, int y, t_frame *frame);

int   is_zoom_mouse_button(int key);
void  switch_zoom_by_mouse(int key, int x, int y, t_frame *frame);

int   is_reset_mouse_button(int key);
void  reset_settings(t_frame *frame);

/*  CLOSE WINDOW  */
int   close_window(t_data *data);

#endif //!KEYS_H