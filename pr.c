

void    b_toa_(t_stack *a, t_stack *b, int cnt)
{
    int pivot1;
    int pivot2;
    int idx;
    int num1;
    int num2;
    int num3;

    if (cnt == 3)
    {
        //TODO 3 sort
        return ;
    }
    while (cnt--)
    {
        if(a->elem[a->rear] <= pivot1)
        {
            rb(a);
            num1++;
        }
        else
        {
            pa(a, b);
            num2++;
            if (a->elem[a->rear] <= pivot2)
            {
                ra(b);
                num3++;
            }
        }
    }
    a_to_b(a, b, num2 - num3);
    idx = -1;
    while (++idx < num3)
        rra(b);
    a_to_b(a, b, num3);
    b_to_a(a, b, num1);
}


void    a_to_b(t_stack *a, t_stack *b, int cnt)
{
    int pivot1;
    int pivot2;
    int idx;
    int num1;
    int num2;
    int num3;

    if (cnt == 3)
    {
        //TODO 3 sort
        return ;
    }
    while (cnt--)
    {
        if(a->elem[a->rear] >= pivot1)
        {
            ra(a);
            num1++;
        }
        else
        {
            pb(a, b);
            num2++;
            if (a->elem[a->rear] >= pivot2)
            {
                rb(b);
                num3++;
            }
        }
    }
    idx = -1;
    while (++idx < num3)
        rrb(b);
    a_to_b(a, b, num1);
    b_to_a(a, b, num3);
    b_to_a(a, b, num2 - num3);
}