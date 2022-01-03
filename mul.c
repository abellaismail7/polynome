#include "polynome.h"
#include <stdio.h>

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
