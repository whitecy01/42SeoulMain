
#include "../head/push_swap.h"

void    push_b(t_stack **b, t_node *change)
{
    t_node *new;
    t_node *location;

    new = create_node(change->content);
    if (!((*b)->top))
        (*b)->top = new;
    else
    {
        location = (*b)->top;
        while(location)
            location = location->next;
        location->next = new;
    }
}

void    pb(t_stack **a, t_stack **b)
{
    t_node  *change;

    change = (*a)->top;
    (*a)->top = (*a)->top->next;
    push_b(b, change);
    (*a)->top->prev = NULL;
    free(change);
    (*a)->bottom->next = (*a)->top;
    //printf("%d", b->size);

}