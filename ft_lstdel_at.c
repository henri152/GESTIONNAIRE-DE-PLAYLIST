#include "list.h"

int	ft_lstdel_at(t_list **lst, int position, void (*del)(void *))
{
	t_list	*prev;
	t_list	*tmp;
	int		i;

	if (lst == NULL || *lst == NULL || position < 0)
		return (-1);
	if (position == 0)
	{
		tmp = *lst;
		*lst = tmp->next;
		ft_lstdelone(tmp, del);
		return (0);
	}
	prev = *lst;
	i = 1;
	while (i < position && prev->next != NULL)
	{
		prev = prev->next;
		i++;
	}
	if (prev->next == NULL)
		return (-1);
	tmp = prev->next;
	prev->next = tmp->next;
	ft_lstdelone(tmp, del);
	return (0);
}
