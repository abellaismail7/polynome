#include "polynome.h"
#include <stdlib.h>
#include <stdio.h>


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
		_poly_add(head, p1, p2->next);
		return;
	}

	_poly_add(head, p1->next, p2);
}


int poly_add(t_poly *p1, t_poly *p2)
{
	t_poly *clone = clone_poly(p1);
	_poly_add(&clone, clone, p2);
	print_poly(clone, 1);
	puts("");
	
	return 1;
}
