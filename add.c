#include "polynome.h"
#include <stdlib.h>
#include <stdio.h>
#include<math.h>

t_coef _cosum(t_coef c1, t_coef c2, int is_add)
{
	c1.dec *= c2.frac;
	c2.dec *= c1.frac;
	c1.frac *= c2.frac;
	c2.frac = c1.frac;

	if(is_add == 1)
		c1.dec += c2.dec;
	else
		c1.dec -= c2.dec;
	return c1;
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

t_coef coadd(t_poly *poly, int val)
{
	t_coef coef;
	t_coef coef_cp;
	coef.dec = 0;
	coef.frac = 1;

	while (poly)
	{
		coef_cp = poly->coef;
		coef_cp.dec *= pow(val, poly->exp);

		coef_cp.dec *= coef.frac;
		coef.dec *= coef_cp.frac;
		coef_cp.frac *= coef.frac;
		coef.frac = coef_cp.frac;

		coef.dec += coef_cp.dec;

		poly = poly->next;
	}
	return coef;
}
