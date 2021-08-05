/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgroot <mgroot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 16:19:11 by mgroot            #+#    #+#             */
/*   Updated: 2021/04/10 10:02:28 by mgroot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 8
# endif

/*
** FD_LIM can be checked with "ulimit -n" in your system
*/
# ifndef FD_LIM
#  define FD_LIM 1025
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_buffer
{
	char		*data;
	size_t		len;
}			t_buffer;

int	get_next_line(int fd, char **line);
int	get_default_buffers(t_buffer *main, t_buffer *tmp);
int	complete_line(char **line, t_buffer *buffer, ssize_t nl_index);
int	read_line(int fd, char **line, t_buffer *main_buffer,
		t_buffer *tmp_buffer);

#endif
