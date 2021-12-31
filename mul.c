#include "polynome.h"
#include <stdio.h>

void add_monome(t_poly **head, t_poly *monome)
{
	if (*head == NULL)
		return;

	t_poly *cur = *head;
	if (cur->exp < monome->exp)
	{
		monome->next = cur;
		*head = monome;
		return ;
	}
	
	t_poly *last = cur;
	while (cur->exp >= monome->exp)
	{
		last = cur;
		if (cur->next == NULL)
			break ;
		cur = cur->next;
	}
	
	monome->next = last->next;
	last->next = monome;

}

void _poly_add(t_poly **head, t_poly *p1, t_poly *p2)
{
	if (p2 == NULL)
		return;
	if (p1 && p1->exp == p2->exp)
	{
		p1->coef = _cosum(p1->coef, p2->coef, 1);
		_poly_add(head, p1->next, p2->next);
		return; 
	}

	if(p1 == NULL || p2->exp > p1->exp)
	{
		t_poly *clone = clone_monome(p2);
		add_monome(head, clone);
		if (p1 == NULL)
			_poly_add(head, NULL, p2->next);
		else
			_poly_add(head, p1->next, p2->next);
		return;
	}

	_poly_add(head, p1->next, p2);
}


void _mul(t_poly *npoly, t_poly poly)
{
	t_poly *cur = npoly;
	while(cur)
	{
		cur->coef.dec *= poly.coef.dec;
		cur->coef.frac *= poly.coef.frac;
		cur->exp += poly.exp;
		cur = cur->next;
	}
}

t_poly *handle__mul(t_poly *p1, t_poly *p2)
{
	if (p1 == NULL)
		return NULL;
	t_poly *npoly = clone_poly(p2);
	_mul(npoly, *p1);
	_poly_add(&npoly, npoly, handle__mul(p1->next, p2));
	return npoly;
}

int handle_mul(t_node *nodes, char *s)
{
	t_poly *p1 = nodes[find_poly(nodes, s[0])].poly;
	t_poly *p2 = nodes[find_poly(nodes, s[2])].poly;
	 	
	t_poly *res = handle__mul(p1, p2);
	print_poly(res, 1);
	puts("");
	return 1;
}
