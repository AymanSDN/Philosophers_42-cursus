#include "philo.h"

t_list *ft_lstnew(void *data)
{
    t_list *node;
    
    node = malloc(sizeof(t_list));
    if (!node)
        return (NULL);
    node->data = data;
    node->next = NULL;
    return (node);
}
