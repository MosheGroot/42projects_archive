#include "frame.h"

#include <pthread.h>
#include <sys/_pthread/_pthread_attr_t.h>
#include <sys/_pthread/_pthread_t.h>

static void update_modifier(t_cnumber *modif, t_frame *frame)
{
  modif->r = ((long double)frame->mouse_pos.x - frame->res_x / 2)
              / frame->zoom;
  modif->i = ((long double)frame->mouse_pos.y - frame->res_x / 2)
              / frame->zoom;
}

static void fill_pos(t_cnumber *pos, uint32_t x, uint32_t y, t_frame *frame)
{
  pos->r = frame->origin.x + ((long double)x - frame->res_x / 2)
            / frame->zoom;
  pos->i = frame->origin.y + ((long double)y - frame->res_y / 2)
            / frame->zoom;
}

static void *render_segment(void *data)
{
  t_render_segment  *segment;
  t_frame           *frame;
  t_cnumber         pos;
  t_col             color;
  uint32_t          iterations;

  segment = (t_render_segment *)data;
  frame = segment->frame;

  for (uint32_t y = segment->begin_y; y < segment->end_y; ++y)
  {
    for (uint32_t x = 0; x < frame->res_x; ++x)
    {
      fill_pos(&pos, x, y, frame);
      iterations = get_fractal_set_function(frame->set)(
                                            pos, segment->modif, 
                                            frame->iterations_limit);
      color = get_fractal_color(frame->colorset,
                                iterations,
                                frame->iterations_limit);
      image_put_pixel(frame->img, x, y, color_to_ui(color));
    }
  }

  pthread_exit(0);
}

void  render_frame(t_frame *frame)
{
  static t_render_segment   segms[FRACTOL_THREADS_NUMBER + 1];
  static pthread_t          thread_ids[FRACTOL_THREADS_NUMBER];
  static pthread_attr_t     attr;
  static t_cnumber          modif = {0, 0};
  uint32_t                  step;

  step = frame->res_y / FRACTOL_THREADS_NUMBER;

  if (frame->interactive)
    update_modifier(&modif, frame);

  segms[0].modif = modif;
  segms[0].frame = frame;
  segms[0].end_y = 0;     // dummy 
  for (uint32_t i = 1; i <= FRACTOL_THREADS_NUMBER; ++i)
  {
    segms[i] = segms[i - 1];
    segms[i].begin_y = segms[i].end_y;
    segms[i].end_y = segms[i].begin_y + step + 1;
    if (segms[i].end_y > frame->res_y)
      segms[i].end_y = frame->res_y;
    pthread_attr_init(&attr);
    pthread_create(thread_ids + i - 1, &attr, &render_segment, segms + i);
  }
  for (uint32_t i = 0; i < FRACTOL_THREADS_NUMBER; ++i)
    pthread_join(thread_ids[i], NULL);
  frame->rendered = 1;
}
