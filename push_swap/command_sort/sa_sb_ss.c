


#include "../head/push_swap.h"

void	sa(t_stack **a)
{
    t_node  *change;
    int     tmp;

    change = (*a)->top;
    change = change->next;
    tmp = change->content;
    change->content = (*a)->top->content;
    (*a)->top->content = tmp;
}

void	sb(t_stack **b)
{
    t_node  *change;
    int     tmp;


    change = (*b)->top;
    change = change->next;
    tmp = change->content;
    change->content = (*b)->top->content;
    (*b)->top->content = tmp;
}


void	ss(t_stack **a, t_stack **b)
{
    sa(a);
    sb(b);
}