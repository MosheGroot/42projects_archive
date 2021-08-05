#include "list.h"

void    lst_remove_elem(t_list *lst, void (*free_data)(void *))
{
    if (!lst)
        return ;
    if (lst->prev)
        lst->prev->next = lst->next;
    if (lst->next)
        lst->next->prev = lst->prev;
    free_data(lst->data);
    free(lst);
}

void    lst_delete(t_list **lst, void (*free_data)(void *))
{
    t_list  *tmp;
    t_list  *begin;
    int     flag;

    if (!lst || !*lst)
        return ;
    flag = 1;
    begin = *lst;
    tmp = *lst;
    while (tmp && (flag || tmp != begin))
    {
        *lst = (*lst)->next;
        free_data(tmp->data);
        free(tmp);
        tmp = *lst;
        if (flag)
            flag--;
    }
    *lst = NULL;
}
