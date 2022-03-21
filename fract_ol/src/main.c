#include "mlx/window.h"
#include "utils/errors.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void  print_help(void)
{
  static const char help[]
    = "Please provide 'default' parametr for default settings\n"
    "or select on of avaliable fractals by their number:\n"
    "1) Mandelbrot set\n"
    "2) Julia set\n"
    "3) Bunring Ship set\n"
    "4) Tricorn set";

  printf("%s\n", help);
  exit(0);
}

t_data  parse_argv(int argc, const char *argv[])
{
  t_data  out;

  if (argc == 1)
  {
    out.frame.set = set_mandelbrot;
    return out;
  }
    
  if (argc > 2)
  {
    log_error("Too much arguments!", 1);
  }
    
  if (!strcmp(argv[1], "help"))
  {
    print_help();
  }
    
  out.frame.set = (enum e_fractal_set)atoi(argv[1]);

  return (out);
}

int main(int argc, const char *argv[])
{
  t_data  data;

  data = parse_argv(argc, argv);
  start_window(&data);
  return (0);
}
