/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgroot <mgroot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 15:31:09 by mgroot            #+#    #+#             */
/*   Updated: 2021/04/10 10:03:11 by mgroot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include <stdlib.h>

typedef struct s_list
{
	void			*data;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;

t_list	*lst_new(void *data);

void	lst_push_front(t_list **lst, t_list *new_el);
void	lst_push_back(t_list **lst, t_list *new_el);
void	lst_push_after(t_list **lst, t_list *new_el);

void	lst_convert_to_cycle(t_list *lst);

void	lst_remove_elem(t_list *lst, void (*free_data)(void *));
void	lst_delete(t_list **lst, void (*free_data)(void *));

#endif
