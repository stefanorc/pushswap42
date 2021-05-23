#include "../push_swap.h"

void	swap(t_stack *stk, t_stack *fuffa)
{
	int tmp;

	(void)fuffa;
	tmp = stk->data[0];
	stk->data[0] = stk->data[1];
	stk->data[1] = tmp;
}

void	rotate(t_stack *stk,  t_stack *fuffa)
{
	int	tmp;
	int	i;

	(void)fuffa;
	if (!stk->len)
		return ;
	i = 0;
	tmp = stk->data[0];
	while (i < stk->len - 1)
	{
		stk->data[i] = stk->data[i + 1];
		i++;
	}
	stk->data[i] = tmp;
}

void	inv_rotate(t_stack *stk, t_stack *fuffa)
{
	int	tmp;
	int	i;

	(void)fuffa;
	if (!stk->len)
		return ;
	i = stk->len - 1;
	tmp = stk->data[stk->len - 1];
	while (i > 0)
	{
		stk->data[i] = stk->data[i - 1];
		i--;
	}
	stk->data[0] = tmp;
}

void	rr(t_stack *stk_a, t_stack * stk_b)
{
	rotate(stk_a, stk_a);
	rotate(stk_b, stk_b);
}

void	rrr(t_stack *stk_a, t_stack * stk_b)
{
	inv_rotate(stk_a, stk_a);
	inv_rotate(stk_b, stk_b);
}

void	push(t_stack *stk_s, t_stack *stk_d)
{
	int	*new_src;
	int	*new_dst;
	int	i;
	
	if (!stk_s->len)
		return ;
	new_src = malloc(sizeof(int) * (stk_s->len - 1));
	new_dst = malloc(sizeof(int) * (stk_d->len + 1));
	new_dst[0] = stk_s->data[0];
	i = stk_s->len;
	while (i > 1)
	{
		new_src[i - 2] = stk_s->data[i - 1];
		i--;
	}
	i = stk_d->len;
	while (i > 0)
	{
		new_dst[i] = stk_d->data[i - 1];
		i--;
	}
	free(stk_s->data);
	free(stk_d->data);
	stk_s->data = new_src;
	stk_d->data= new_dst;
	stk_d->len++;
	stk_s->len--;
}

int	min_stack(t_stack *stack)
{
	int res;
	int	i;

	res = stack->data[0];
	i = 0;
	while (i < stack->len)
	{
		if (stack->data[i] < res)
			res = stack->data[i];
		i++;
	}
	return (res);
}

int	max_stack(t_stack **stack, int len)
{
	int res;
	int	i;

	res = stack[0]->len;
	i = 0;
	while (i < len)
	{
		if (stack[i]->len > res)
			res = stack[i]->len;
		i++;
	}
	return (res);
}

t_stack	*stack_dup(int *data, int len)
{
	t_stack	*dst;
	int		i;
	
	dst = malloc(sizeof(t_stack));
	dst->data = malloc(sizeof(int) * len);
	dst->len = len;
	i = len;
	while (i > 0)
	{
		i--;
		dst->data[i] = data[i];
	}
	return (dst);
}

void	print_stack(t_stack *src)
{
	int i;
	
	printf("stack len: %d\n", src->len);
	i = 0;
	while (i < src->len)
	{
		printf("%d\n", src->data[i]);
		i++;
	}
	printf("stack end\n");
}

void	LIS(t_stack *stk_s, t_stack **stk_d)
{
	t_stack *dup;
	t_stack **reg;
	int	i;
	int	j;

	dup = stack_dup(stk_s->data, stk_s->len);
	while (min_stack(dup) != dup->data[0])
		rotate(dup, dup);
	reg = malloc(sizeof(t_stack *) * (dup->len));
	i = 0;
	while (i < stk_s->len)
	{
		reg[i] = malloc(sizeof(t_stack));
		reg[i]->data = malloc(sizeof(int) * (dup->len));
		reg[i]->len = 0;
		i++;
	}
	reg[0]->data[0] = dup->data[0];
	reg[0]->len++;
	i = 1;
	while (i < dup->len)
	{
		j = 0;
		while (j < i)
		{
			if (dup->data[j] < dup->data[i] && reg[i]->len < reg[j]->len)
			{
				free(reg[i]->data);
				free(reg[i]);
				reg[i] = stack_dup(reg[j]->data, stk_s->len);
				reg[i]->len = reg[j]->len;
			}
			j++;
		}
		reg[i]->data[reg[i]->len] = dup->data[i];
		reg[i]->len++;
		i++;
	}
	i = max_stack(reg, dup->len);
	j = 0;
	while (i != reg[j]->len)
	{
		j++;
	}
	free((*stk_d)->data);
	free(*stk_d);
	*stk_d = stack_dup(reg[j]->data, reg[j]->len);
	i = 0;
	while (i < stk_s->len)
	{
		free(reg[i]->data);
		free(reg[i]);
		i++;
	}
	free(reg);
	free(dup->data);
	free(dup);
}
/*
int	check_lis(t_stack *stk_a, t_stack *stk_b, t_stack *lis)
{
	t_stack *tmp;
	
	tmp = malloc(sizeof(t_stack));
	tmp->data = malloc(0);
	tmp->len = 0;
	push(stk_b, stk_a);
	LIS(stk_a, &tmp);
	if (tmp->len > lis->len)
	{
		free(lis->data);
		lis->data = tmp->data;
		lis->len = tmp->len;
		free(tmp);
		return (1);
	}
	push(stk_a, stk_b);
	free(tmp->data);
	free(tmp);
	return (0);
}
*/
void loop_move(int n, void (*f)(t_stack *, t_stack *), t_stack *stk_a, t_stack *stk_b)
{
	while (n--)
		f(stk_a, stk_b);
}

int	make_moves(t_moves *to_do, t_stack *stk_a, t_stack *stk_b)
{
	int	count;

	if (to_do->opt_code == 0)
	{
		if (to_do->moves_a > to_do->moves_b)
		{
			loop_move(to_do->moves_b, &rr, stk_a, stk_b);
			loop_move(to_do->moves_a - to_do->moves_b, &rotate, stk_a, stk_a);
			count = to_do->moves_a;
		}
		else
		{
			loop_move(to_do->moves_a, &rr, stk_a, stk_b);
			loop_move(to_do->moves_b - to_do->moves_a, &rotate, stk_b, stk_b);
			count = to_do->moves_b;
		}
	}
	if (to_do->opt_code == 3)
	{
		if (to_do->moves_a > to_do->moves_b)
		{
			loop_move(to_do->moves_b, &rrr, stk_a, stk_b);
			loop_move(to_do->moves_a - to_do->moves_b, &inv_rotate, stk_a, stk_a);
			count = to_do->moves_a;
		}
		else
		{
			loop_move(to_do->moves_a, &rrr, stk_a, stk_b);
			loop_move(to_do->moves_b - to_do->moves_a, &inv_rotate, stk_b, stk_b);
			count = to_do->moves_b;
		}
	}
	if (to_do->opt_code == 1)
	{
		loop_move(to_do->moves_a, &rotate, stk_a, stk_a);
		loop_move(to_do->moves_b, &inv_rotate, stk_b, stk_b);
		count = to_do->moves_a + to_do->moves_b;
	}
	if (to_do->opt_code == 2)
	{
		loop_move(to_do->moves_b, &rotate, stk_b, stk_b);
		loop_move(to_do->moves_a, &inv_rotate, stk_a, stk_a);
		count = to_do->moves_a + to_do->moves_b;
	}
	return (count);
}

int main(int argc, char **argv)
{
	t_stack *arrA;
	t_stack *arrB;
	t_stack *lis;
	t_stack *dup;
	t_stack *dup_lis;
	t_moves *to_do;
	int count;
	int spot;

	count = 0;
	arrA = parser(argc, argv);
	arrB = malloc(sizeof(t_stack));
	lis = malloc(sizeof(t_stack));
	arrB->data = malloc(0);
	arrB->len = 0;
	lis->data = malloc(0);
	lis->len = 0;
	LIS(arrA, &lis);
	//print_stack(lis);
	dup_lis = malloc(sizeof(t_stack));
	dup_lis->data = malloc(0);
	dup_lis->len = 0;
	while (arrA->len > lis->len)
	{
		dup = stack_dup(arrA->data, arrA->len);
		swap(dup, dup);
		LIS(dup, &dup_lis);
		free(dup->data);
		free(dup);
		if (dup_lis->len > lis->len)
		{
			swap(arrA, arrA);
			LIS(arrA, &lis);
			write(1, "sa\n", 3);
			count++;
			continue ;
		}
		to_do = predict_moves(arrA, arrB, lis);
		count += make_moves(to_do, arrA, arrB);
		print_moves(to_do);
		free(to_do);
		push(arrA, arrB);
		write(1, "pb\n", 3);
		count++;
	}
	while (arrB->len)
	{
		spot = find_inv_spot(arrA, arrB->data[0]);
		if (spot < arrA->len / 2.0)
		{
			loop_move(spot, &rotate, arrA, arrA);
			print_moves(&(t_moves){spot, 0, 0, 1});
			count += spot;
		}
		else
		{
			loop_move(arrA->len - spot, &inv_rotate, arrA, arrA);
			print_moves(&(t_moves){arrA->len - spot, 0, 0, 2});
			count += arrA->len - spot;
		}
		push(arrB, arrA);
		write(1, "pa\n", 3);
		count++;
	}
	spot = min_in_arr(*arrA);
	if (spot < arrA->len / 2.0)
	{
		loop_move(spot, &rotate, arrA, arrA);
		print_moves(&(t_moves){spot, 0, 0, 1});
		count += spot;
	}
	else
	{
		loop_move(arrA->len - spot, &inv_rotate, arrA, arrA);
		print_moves(&(t_moves){arrA->len - spot, 0, 0, 2});
		count += arrA->len - spot;
	}
	//print_stack(arrA);
	free(arrB->data);
	free(arrB);
	free(dup_lis->data);
	free(dup_lis);
	free(arrA->data);
	free(arrA);
	free(lis->data);
	free(lis);
	//check_stack(arrA, "cre");
	//printf("mosse : %d\n", count);
	return 1;
}