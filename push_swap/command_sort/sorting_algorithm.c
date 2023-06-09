

#include "../head/push_swap.h"

void    sort_algorithm(t_stack **a, t_stack **b, int array_size)
{
    printf("b size  : %d %d\n",(*b)->size, array_size);

   pb(a, b);
    t_node *s;
    s = (*a)->top;
    int i = 0;
    while (i < array_size + 1)
    {
        printf("a[%d] : %d\n", i , s->content);
        i++;
        s = s->next;
    }
    printf("b->top->content : %d\n", (*b)->top->content);
}