#include "list.h"

void	ft_lstadd_at(t_list **lst, t_list *new, int position)
{
	t_list	*prev;
	int		i;

	if (lst == NULL || new == NULL)
		return ;
	if (position <= 0 || *lst == NULL)
	{
		new->next = *lst;
		*lst = new;
		return ;
	}
	prev = *lst;
	i = 1;
	while (i < position && prev->next != NULL)
	{
		prev = prev->next;
		i++;
	}
	new->next = prev->next;
	prev->next = new;
}
