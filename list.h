#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

typedef struct s_list
{
    void            *content;
    struct s_list   *next;
}   t_list;

t_list  *ft_lstnew(void *content);
int     ft_lstsize(t_list *lst);
void    ft_lstdelone(t_list *lst, void (*del)(void *));
void    ft_lstclear(t_list **lst, void (*del)(void *));
void    ft_lstiter(t_list *lst, void (*f)(void *));
void    ft_lstadd_at(t_list **lst, t_list *new, int position);
int     ft_lstdel_at(t_list **lst, int position, void (*del)(void *));

#endif // LIST_H

