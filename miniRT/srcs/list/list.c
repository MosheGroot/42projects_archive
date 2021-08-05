#include "list.h"

t_list  *lst_new(void *data)
{
    t_list  *ptr;

    ptr = malloc(sizeof(t_list));
    if (!ptr)
        return (NULL);
    ptr->next = NULL;
    ptr->prev = NULL;
    ptr->data = data;
    return (ptr);
}

void    lst_push_front(t_list **lst, t_list *new_el)
{
    if (!lst || !new_el)
        return ;
    if (!*lst)
    {
        *lst = new_el;
        return ;
    }
    new_el->next = *lst;
    (*lst)->prev = new_el;
    *lst = new_el;
}

void    lst_push_back(t_list **lst, t_list *new_el)
{
    t_list  *tmp;

    if (!lst || !new_el)
        return ;
    if (!*lst)
    {
        *lst = new_el;
        return ;
    }
    tmp = *lst;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_el;
    new_el->prev = tmp;
}

void    lst_push_after(t_list **lst, t_list *new_el)
{
    if (!lst)
        return ;
    if (!*lst)
    {
        *lst = new_el;
        return ;
    }
    if ((*lst)->next)
        (*lst)->next->prev = new_el;
    new_el->next = (*lst)->next;
    new_el->prev = *lst;
    (*lst)->next = new_el;
}

void    lst_convert_to_cycle(t_list *lst)
{
    t_list  *tmp;

    if (!lst)
        return ;
    tmp = lst;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = lst;
    lst->prev = tmp;
}
